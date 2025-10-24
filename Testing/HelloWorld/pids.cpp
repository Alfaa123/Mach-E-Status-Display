#include <ESP32-TWAI-CAN.hpp>
#include "screenVariables.h"
#include <Arduino.h>

void printDebugInfo(CanFrame frame) {
  Serial.print("Response Recieved From ");
  Serial.println(frame.identifier, HEX);
  Serial.print("Data: ");
  Serial.print(frame.data[0], HEX);
  Serial.print(" ");
  Serial.print(frame.data[1], HEX);
  Serial.print(" ");
  Serial.print(frame.data[2], HEX);
  Serial.print(" ");
  Serial.print(frame.data[3], HEX);
  Serial.print(" ");
  Serial.print(frame.data[4], HEX);
  Serial.print(" ");
  Serial.print(frame.data[5], HEX);
  Serial.print(" ");
  Serial.print(frame.data[6], HEX);
  Serial.print(" ");
  Serial.println(frame.data[7], HEX);
}

void updateBatteryLevel(CanFrame frame) {
  float batLevel = (frame.data[4] * 256 + frame.data[5]) * 0.002;
  set_var_battery_level_float(batLevel);
  char buffer[7];
  sprintf(buffer, "%.2f%%", batLevel);
  set_var_battery_level(buffer);
}
