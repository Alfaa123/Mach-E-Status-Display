#include <ESP32-TWAI-CAN.hpp>
#include "screenVariables.h"
#include <Arduino.h>

float primaryMotorTorque = 0;
float secondaryMotorTorque = 0;

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

void updatePrimaryMotorTorque(CanFrame frame) {
  primaryMotorTorque = (int8_t(frame.data[4]) * 256 + frame.data[5]) * 0.1;
  char buffer[10];
  sprintf(buffer, "%.1f nM", primaryMotorTorque);
  set_var_primary_motor_torque(buffer);
}

void updateSecondaryMotorTorque(CanFrame frame) {
  secondaryMotorTorque = (int8_t(frame.data[4]) * 256 + frame.data[5]) * 0.1;
  char buffer[10];
  sprintf(buffer, "%.1f nM", secondaryMotorTorque);
  set_var_secondary_motor_torque(buffer);
}

void updateTorqueSplit(){
  float total = primaryMotorTorque + secondaryMotorTorque;
  if (total > 5 || total < -5){  
    float ratio = (primaryMotorTorque / total) * 100;
    set_var_torque_split(ratio);}
  else {set_var_torque_split(50);}

}
