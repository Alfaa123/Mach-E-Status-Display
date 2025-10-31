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
#include "pids.hpp"



#define CAN_TX 6
#define CAN_RX 0

CanFrame rxFrame;

TaskHandle_t DisplayLoopHandle;

uint32_t screenWidth;
uint32_t screenHeight;
uint32_t bufSize;
lv_display_t *disp;
lv_color_t *disp_draw_buf;

TCA9534 TCA(0x20);
#define GFX_BL 1

void sendObdFrame(uint16_t CANId);



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
  1 /* vsync_polarity */, 10 /* vsync_front_porch */, 8 /* vsync_pulse_width */, 20 /* vsync_back_porch */, 0 /* pclk_active_neg */, 12000000 /* prefer_speed */,
    0 /* de_idle_high */, 0 /* pclk_idle_high */, 0 /* bounce_buffer_size_px */);
Arduino_RGB_Display *gfx = new Arduino_RGB_Display(
  480 /* width */, 480 /* height */, rgbpanel, 0 /* rotation */, true /* auto_flush */,
  bus, GFX_NOT_DEFINED /* RST */, st7701_type1_init_operations, sizeof(st7701_type1_init_operations));
/*******************************************************************************
 * End of Arduino_GFX setting
 ******************************************************************************/

static portMUX_TYPE CAN_spinlock = portMUX_INITIALIZER_UNLOCKED;


void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
  //uint32_t w = lv_area_get_width(area);
  //uint32_t h = lv_area_get_height(area);

  //gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)px_map, w, h);
  //taskENTER_CRITICAL(&displayFlush_spinlock);
  //gfx->draw16bitRGBBitmap(0, 0, (uint16_t *)disp_draw_buf, 480, 480);
  //taskEXIT_CRITICAL(&displayFlush_spinlock);
  /*Call it to tell LVGL you are ready*/
  lv_disp_flush_ready(disp);
}

void DisplayLoop(void *pvParameters) {
    Serial.print("Display Loop started on core ");
  Serial.println(xPortGetCoreID());
  for (;;) {
    ui_tick();
    lv_task_handler();
    gfx->draw16bitRGBBitmap(0, 0, (uint16_t *)disp_draw_buf, 480, 480);
    //gfx->flush();
    delay(5);
  }
}

void MessageHandler(void *pvParameters) {
  Serial.print("Message Handler started on core ");
  Serial.println(xPortGetCoreID());
  for (;;) {
    if (ESP32Can.readFrame(rxFrame, 1000)) {
      if (rxFrame.identifier != 0x59E) {
        if (rxFrame.data[1] == 0x7F) {
          Serial.println("Negative Response:");
          printDebugInfo(rxFrame);
          Serial.println();
        }
        Serial.print("Response from: ");
        Serial.println(rxFrame.identifier, HEX);
        if (rxFrame.data[1] == 0x22 + 0x40) {
          //Replies sent to 0x7E6
          if (rxFrame.identifier == 0x7EE) {
            if (rxFrame.data[2] == 0x48 && rxFrame.data[3] == 0x1F) {
              updatePrimaryMotortemp(rxFrame);
            }
            if (rxFrame.data[2] == 0x48 && rxFrame.data[3] == 0xe0) {
              updateHVBThermalMode(rxFrame);
            }
            if (rxFrame.data[2] == 0x48 && rxFrame.data[3] == 0xDE) {
              updateCoolantHeaterPower(rxFrame);
            }
            if (rxFrame.data[2] == 0x48 && rxFrame.data[3] == 0xDF) {
              updateCoolantHeaterMode(rxFrame);
            }
          }
          //Replies sent to 0x7E7
          if (rxFrame.identifier == 0x7EF) {
            if (rxFrame.data[2] == 0x48 && rxFrame.data[3] == 0x20) {
              updateSecondaryMotortemp(rxFrame);
            }
          }
          //Replies sent to 0x7E4
          if (rxFrame.identifier == 0x7EC) {
            if (rxFrame.data[2] == 0x48 && rxFrame.data[3] == 0xF9) {
              updateBatteryCurrent(rxFrame);
            }
            if (rxFrame.data[2] == 0x48 && rxFrame.data[3] == 0x01) {
              updateBatteryLevel(rxFrame);
            }
            if (rxFrame.data[2] == 0x48 && rxFrame.data[3] == 0x00) {
              updateHVBTemp(rxFrame);
            }
            if (rxFrame.data[2] == 0x48 && rxFrame.data[3] == 0x0D) {
              updateBatteryVoltage(rxFrame);
            }
          }
          //Replies sent to 0x7E0
          if (rxFrame.identifier == 0x7E8) {
            if (rxFrame.data[2] == 0xF4 && rxFrame.data[3] == 0x67) {
              updateHeaterLoopTemp(rxFrame);
            }
          }
          //Replies sent to 0x7E2
          if (rxFrame.identifier == 0x7EA) {
            if (rxFrame.data[2] == 0xDD && rxFrame.data[3] == 0x04) {
              updateInteriorTemp(rxFrame);
            }
          }
        }
      }
    }
    delay(5);
  }
}

void PeriodicRequestsFullSpeed(void *pvParameters) {
  Serial.print("Periodic Full Speed CAN requests started on core ");
  Serial.println(xPortGetCoreID());
  for (;;) {
        //Battery Current
    sendUDSRequest(0x7E4, 0x48f9);
    delay(200);
  }
}

void PeriodicRequests1s(void *pvParameters) {
    if (ESP32Can.begin(ESP32Can.convertSpeed(500), CAN_TX, CAN_RX, 10, 10)) {
    Serial.println("CAN bus started!");
  } else {
    Serial.println("CAN bus failed!");
  }
  Serial.print("Periodic 1s CAN requests started on core ");
  Serial.println(xPortGetCoreID());
  for (;;) {
    //HVB Thermal Mode
    sendUDSRequest(0x7E6, 0x48e0);
    //Battery SoC
    sendUDSRequest(0x7E4, 0x4801);
    //Interior Temperature
    sendUDSRequest(0x7E2, 0xDD04);
    delay(300);
    //HVB Temp
    sendUDSRequest(0x7E4, 0x4800);
    //Primary Motor temp
    sendUDSRequest(0x7E6, 0x481f);
    //Secondary Motor temp
    sendUDSRequest(0x7E7, 0x4820);
    //Heater Loop Temp
    sendUDSRequest(0x7E0, 0xF467);
    delay(300);
    //Coolant Heater Power
    sendUDSRequest(0x7E6, 0x48de);
    //Battery Voltage
    sendUDSRequest(0x7E4, 0x480D);
    delay(300);
    //Coolant Heater Mode
    sendUDSRequest(0x7E6, 0x48df);
    delay(300);
  }
}


void setup(void) {
  delay(2000);
  Serial.begin(115200);
  Serial.print("Setup started on core ");
  Serial.println(xPortGetCoreID());

  if (Wire.begin(15, 7)) {
    Serial.println("I2C Bus Started!");
  } else {
    Serial.println("I2C Bus Failed!");
  }

  TCA.begin();

  Wire.setClock(50000);
    // Init Display
  if (gfx->begin()) {
    Serial.println("LCD Started!");
  } else {
    Serial.println("LCD Failed!");
  }
  gfx->fillScreen(RGB565_BLACK);
  lv_init();
  lv_tick_set_cb(millis);
  Serial.println("LVGL Started");
  screenWidth = gfx->width();
  screenHeight = gfx->height();
  bufSize = screenWidth * screenHeight;
  //disp_draw_buf = (lv_color_t *)gfx->getFramebuffer();
  disp_draw_buf = (lv_color_t *)heap_caps_malloc(bufSize * 2, MALLOC_CAP_8BIT);
  if (!disp_draw_buf) {
    Serial.println("LVGL disp_draw_buf allocate failed!");
  } else {
    disp = lv_display_create(screenWidth, screenHeight);
    lv_display_set_buffers(disp, disp_draw_buf, NULL, bufSize * 2, LV_DISPLAY_RENDER_MODE_DIRECT);
    lv_display_set_flush_cb(disp, my_disp_flush);
  }
  ui_init();
  Serial.println("UI Started");

 xTaskCreatePinnedToCore(
    PeriodicRequests1s,   /* Task function. */
    "PeriodicRequests1s", /* name of task. */
    2000,                /* Stack size of task */
    NULL,                 /* parameter of the task */
    1,                    /* priority of the task */
    NULL,                 /* Task handle to keep track of created task */
    1);                   /* pin task to core 0 */

  xTaskCreatePinnedToCore(
    PeriodicRequestsFullSpeed,   /* Task function. */
    "PeriodicRequestsFullSpeed", /* name of task. */
    2000,                       /* Stack size of task */
    NULL,                        /* parameter of the task */
    2,                           /* priority of the task */
    NULL,                        /* Task handle to keep track of created task */
    1);                          /* pin task to core 0 */

  xTaskCreatePinnedToCore(
    MessageHandler,        /* Task function. */
    "MessageHandler",      /* name of task. */
    5000,                 /* Stack size of task */
    NULL,                  /* parameter of the task */
    3,                     /* priority of the task */
    NULL, /* Task handle to keep track of created task */
    1);


#ifdef GFX_BL
  TCA.pinMode1(GFX_BL, OUTPUT);
  TCA.write1(GFX_BL, HIGH);
#endif
xTaskCreatePinnedToCore(
    DisplayLoop,        /* Task function. */
    "DisplayLoop",      /* name of task. */
    100000,              /* Stack size of task */
    NULL,               /* parameter of the task */
    5,                  /* priority of the task */
    &DisplayLoopHandle, /* Task handle to keep track of created task */
    0);                 /* pin task to core 0 */
}
void loop() {
}

void sendUDSRequest(uint16_t CANId, uint16_t PID) {
  
  Serial.print("UDS Request Sent To: 0x");
  Serial.print(CANId, HEX);
  Serial.print(" For PID: 0x");
  Serial.println(PID, HEX);
  CanFrame obdFrame = { 0 };
  uint8_t lower = PID & 0xff;
  uint8_t upper = (PID >> 8) & 0xff;
  obdFrame.identifier = CANId;  // Default OBD2 address;
  obdFrame.extd = 0;
  obdFrame.data_length_code = 8;
  obdFrame.data[0] = 0x03;
  obdFrame.data[1] = 0x22;
  obdFrame.data[2] = upper;
  obdFrame.data[3] = lower;  // Best use 0xAA (0b10101010) instead of 0
  obdFrame.data[4] = 0xAA;   // TWAI / CAN works better this way, as it
  obdFrame.data[5] = 0xAA;   // needs to avoid bit-stuffing
  obdFrame.data[6] = 0xAA;
  obdFrame.data[7] = 0xAA;
  // Accepts both pointers and references
  taskENTER_CRITICAL(&CAN_spinlock);
  ESP32Can.writeFrame(obdFrame);  // timeout defaults to 1 ms
  taskEXIT_CRITICAL(&CAN_spinlock);
}

// void sendUDSMultiRequest(uint16_t CANId, uint16_t PID) {
//   Serial.print("UDS Request Sent To: 0x");
//   Serial.print(CANId, HEX);
//   Serial.print(" For PID: 0x");
//   Serial.println(PID, HEX);
//   CanFrame obdFrame = { 0 };
//   uint8_t lower = PID & 0xff;
//   uint8_t upper = (PID >> 8) & 0xff;
//   obdFrame.identifier = CANId;  // Default OBD2 address;
//   obdFrame.extd = 0;
//   obdFrame.data_length_code = 8;
//   obdFrame.data[0] = 0x04;
//   obdFrame.data[1] = 0x2A;
//   obdFrame.data[2] = 0x03;
//   obdFrame.data[3] = upper;  // Best use 0xAA (0b10101010) instead of 0
//   obdFrame.data[4] = lower;  // TWAI / CAN works better this way, as it
//   obdFrame.data[5] = 0xAA;   // needs to avoid bit-stuffing
//   obdFrame.data[6] = 0xAA;
//   obdFrame.data[7] = 0xAA;
//   // Accepts both pointers and references
//   ESP32Can.writeFrame(obdFrame);  // timeout defaults to 1 ms
// }