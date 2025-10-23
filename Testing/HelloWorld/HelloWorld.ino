/*******************************************************************************
 * Start of Arduino_GFX setting
 *
 * Arduino_GFX try to find the settings depends on selected board in Arduino IDE
 * Or you can define the display dev kit not in the board list
 * Defalult pin list for non display dev kit:
 * Arduino Nano, Micro and more: CS:  9, DC:  8, RST:  7, BL:  6, SCK: 13, MOSI: 11, MISO: 12
 * ESP32 various dev board     : CS:  5, DC: 27, RST: 33, BL: 22, SCK: 18, MOSI: 23, MISO: nil
 * ESP32-C3 various dev board  : CS:  7, DC:  2, RST:  1, BL:  3, SCK:  4, MOSI:  6, MISO: nil
 * ESP32-S2 various dev board  : CS: 34, DC: 38, RST: 33, BL: 21, SCK: 36, MOSI: 35, MISO: nil
 * ESP32-S3 various dev board  : CS: 40, DC: 41, RST: 42, BL: 48, SCK: 36, MOSI: 35, MISO: nil
 * ESP8266 various dev board   : CS: 15, DC:  4, RST:  2, BL:  5, SCK: 14, MOSI: 13, MISO: 12
 * Raspberry Pi Pico dev board : CS: 17, DC: 27, RST: 26, BL: 28, SCK: 18, MOSI: 19, MISO: 16
 * RTL8720 BW16 old patch core : CS: 18, DC: 17, RST:  2, BL: 23, SCK: 19, MOSI: 21, MISO: 20
 * RTL8720_BW16 Official core  : CS:  9, DC:  8, RST:  6, BL:  3, SCK: 10, MOSI: 12, MISO: 11
 * RTL8722 dev board           : CS: 18, DC: 17, RST: 22, BL: 23, SCK: 13, MOSI: 11, MISO: 12
 * RTL8722_mini dev board      : CS: 12, DC: 14, RST: 15, BL: 13, SCK: 11, MOSI:  9, MISO: 10
 * Seeeduino XIAO dev board    : CS:  3, DC:  2, RST:  1, BL:  0, SCK:  8, MOSI: 10, MISO:  9
 * Teensy 4.1 dev board        : CS: 39, DC: 41, RST: 40, BL: 22, SCK: 13, MOSI: 11, MISO: 12
 ******************************************************************************/
#include <lvgl.h>

#include <Arduino_GFX_Library.h>
#include "TCA9554.h"
#include <ESP32-TWAI-CAN.hpp>
#include "ui.h"

#include <string.h>
#include "vars.h"

#include "screenVariables.h"



#define CAN_TX		6
#define CAN_RX		0

CanFrame rxFrame;

TaskHandle_t PeriodicRequestsHandle;

uint32_t screenWidth;
uint32_t screenHeight;
uint32_t bufSize;
lv_display_t *disp;
lv_color_t *disp_draw_buf;

TCA9534 TCA(0x20);
#define GFX_BL 1

void sendObdFrame(uint8_t obdId);



//HWCDC USBSerial;
Arduino_DataBus *bus = new Arduino_SWSPI(
    GFX_NOT_DEFINED /* DC */, 42 /* CS */,
    2 /* SCK */, 1 /* MOSI */, GFX_NOT_DEFINED /* MISO */);

Arduino_ESP32RGBPanel *rgbpanel = new Arduino_ESP32RGBPanel(
    40 /* DE */, 39 /* VSYNC */, 38 /* HSYNC */, 41 /* PCLK */,
    46 /* R0 */, 3 /* R1 */, 8 /* R2 */, 18 /* R3 */, 17 /* R4 */,
    14 /* G0 */, 13 /* G1 */, 12 /* G2 */, 11 /* G3 */, 10 /* G4 */, 9 /* G5 */,
    5 /* B0 */, 45 /* B1 */, 48 /* B2 */, 47 /* B3 */, 21 /* B4 */,
    1 /* hsync_polarity */, 10 /* hsync_front_porch */, 8 /* hsync_pulse_width */, 50 /* hsync_back_porch */,
    1 /* vsync_polarity */, 10 /* vsync_front_porch */, 8 /* vsync_pulse_width */, 20 /* vsync_back_porch */);
Arduino_RGB_Display *gfx = new Arduino_RGB_Display(
    480 /* width */, 480 /* height */, rgbpanel, 0 /* rotation */, true /* auto_flush */,
    bus, GFX_NOT_DEFINED /* RST */, st7701_type1_init_operations, sizeof(st7701_type1_init_operations));
/*******************************************************************************
 * End of Arduino_GFX setting
 ******************************************************************************/

void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
  //uint32_t w = lv_area_get_width(area);
  //uint32_t h = lv_area_get_height(area);

  //gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)px_map, w, h);
  gfx->draw16bitRGBBitmap(0, 0, (uint16_t *)px_map, 480, 480);
  /*Call it to tell LVGL you are ready*/
  lv_disp_flush_ready(disp);
}

void my_print(lv_log_level_t level, const char *buf)
{
  LV_UNUSED(level);
  Serial.println(buf);
  Serial.flush();
}

void PeriodicRequests( void * pvParameters){
  Serial.print("Periodic CAN requests started on core ");
  Serial.println(xPortGetCoreID());

  while(1==1){
    static unsigned long lastTime = 0;
    if (millis() > lastTime + 1000){
      lastTime = millis();
      sendObdFrame(0);
      //Serial.println("Sent CAN Request");
    }


    if(ESP32Can.readFrame(rxFrame, 1000)) {
        Serial.printf("Received frame: %03X  \r\n", rxFrame.identifier);
        if(rxFrame.data[1] = 0x7F){
          Serial.print("Negative Response Recieved From ");
          Serial.print(rxFrame.identifier);
          Serial.print(": SID: ");
          Serial.print(rxFrame.data[2]);
          Serial.print(" NRC: ");
          Serial.println(rxFrame.data[3]);
        }
        if(rxFrame.identifier == 0x7E8) {            
            Serial.print("Data: ");
            Serial.print(rxFrame.data[0], HEX);
            Serial.print(" ");
            Serial.print(rxFrame.data[1], HEX);
                        Serial.print(" ");
            Serial.print(rxFrame.data[2], HEX);
                        Serial.print(" ");
            Serial.print(rxFrame.data[3], HEX);
                        Serial.print(" ");
            Serial.print(rxFrame.data[4], HEX);
                        Serial.print(" ");
            Serial.print(rxFrame.data[5], HEX);
                        Serial.print(" ");
            Serial.print(rxFrame.data[6], HEX);
                        Serial.print(" ");
            Serial.println(rxFrame.data[7], HEX);                     
}
}
  }
}

void setup(void)
{
delay(2000);
Serial.begin(115200);
Serial.print("Setup started on core ");
Serial.println(xPortGetCoreID());

xTaskCreatePinnedToCore(
                    PeriodicRequests,   /* Task function. */
                    "PeriodicRequests",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &PeriodicRequestsHandle,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */     

if(ESP32Can.begin(ESP32Can.convertSpeed(500), CAN_TX, CAN_RX, 10, 10)) {
  Serial.println("CAN bus started!");
} else {
  Serial.println("CAN bus failed!");
}

if(Wire.begin(15,7)){
  Serial.println("I2C Bus Started!");
} else {
  Serial.println("I2C Bus Failed!");
}

TCA.begin();

Wire.setClock(50000);

#ifdef DEV_DEVICE_INIT
  DEV_DEVICE_INIT();
#endif


  // Init Display
  if (gfx->begin()){
    Serial.println("LCD Started!");
  } else{
    Serial.println("LCD Failed!");
  }
  gfx->fillScreen(RGB565_BLACK);

#ifdef GFX_BL
  TCA.pinMode1(GFX_BL, OUTPUT);
  TCA.write1(GFX_BL, HIGH);
#endif

lv_init();
lv_tick_set_cb(millis);
Serial.println("LVGL Started");



//lv_log_register_print_cb(my_print);

screenWidth = gfx->width();
screenHeight = gfx->height();

bufSize = screenWidth * screenHeight;

disp_draw_buf = (lv_color_t *)gfx->getFramebuffer();

if (!disp_draw_buf)
{
  Serial.println("LVGL disp_draw_buf allocate failed!");
}
else
{
disp = lv_display_create(screenWidth, screenHeight);
lv_display_set_buffers(disp, disp_draw_buf, NULL, bufSize * 2, LV_DISPLAY_RENDER_MODE_DIRECT);
lv_display_set_flush_cb(disp, my_disp_flush);
}
ui_init();
Serial.println("UI Started");
//lv_obj_t *label = lv_label_create(lv_scr_act());
// lv_label_set_text(label, "Hello Arduino, I'm LVGL!(V" GFX_STR(LVGL_VERSION_MAJOR) "." GFX_STR(LVGL_VERSION_MINOR) "." GFX_STR(LVGL_VERSION_PATCH) ")");
//lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

}
void loop()
{
  lv_timer_handler();
  ui_tick();
  

}

void sendObdFrame(uint8_t obdId) {
    CanFrame obdFrame         = {0};
    obdFrame.identifier       = 0x7E0; // Default OBD2 address;
    obdFrame.extd             = 0;
    obdFrame.data_length_code = 8;
    obdFrame.data[0]          = 0x03;
    obdFrame.data[1]          = 0x22;
    obdFrame.data[2]          = 0x39;
    obdFrame.data[3]          = 0x87; // Best use 0xAA (0b10101010) instead of 0
    obdFrame.data[4]          = 0xAA; // TWAI / CAN works better this way, as it
    obdFrame.data[5]          = 0xAA; // needs to avoid bit-stuffing
    obdFrame.data[6]          = 0xAA;
    obdFrame.data[7]          = 0xAA;
    // Accepts both pointers and references
    ESP32Can.writeFrame(obdFrame); // timeout defaults to 1 ms
}