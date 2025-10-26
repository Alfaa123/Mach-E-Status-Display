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

void updateHVBTemp(CanFrame frame) {
  float batTemp = (frame.data[4] - 50) * 1.8 + 32;
  char buffer[8];
  sprintf(buffer, "%.1f °f", batTemp);
  set_var_hvb_temp(buffer);
}

void updateHVBThermalMode(CanFrame frame) {
  switch (frame.data[4]) {
    case 0:
      set_var_hvb_thermal_mode("Off");
      break;
    case 1:
    set_var_hvb_thermal_mode("Equalizing");
      break;
    case 2:
    set_var_hvb_thermal_mode("Cooling - Flow");
      break;
    case 3:
    set_var_hvb_thermal_mode("Cooling - Fan");
      break;
    case 4:
    set_var_hvb_thermal_mode("Cooling - Mod Chill");
      break;
    case 5:
    set_var_hvb_thermal_mode("Cooling - Max Chill");
      break;
    case 15:
    set_var_hvb_thermal_mode("Heating");
      break;
  }
  
}

void updatePrimaryMotortemp(CanFrame frame) {
  float primaryMotortemp = (int8_t(frame.data[4]) * 256 + frame.data[5]) * 1.8+32;
  char buffer[10];
  sprintf(buffer, "%.1f °f", primaryMotortemp);
  set_var_primary_motor_temp(buffer);
}

void updateSecondaryMotortemp(CanFrame frame) {
  float secondaryMotortemp = (int8_t(frame.data[4]) * 256 + frame.data[5])  * 1.8+32;
  char buffer[10];
  sprintf(buffer, "%.1f °f", secondaryMotortemp);
  set_var_secondary_motor_temp(buffer);
}

void updateCoolantHeaterPower(CanFrame frame){
  int16_t coolantHeaterPower = (frame.data[4] << 8) | frame.data[5];
  float coolantHeaterPowerFloat = coolantHeaterPower * 0.001;
  char buffer[9];
  sprintf(buffer, "%.3f kW", coolantHeaterPower);
  set_var_coolant_heater_power(buffer);
}

void updateCoolantHeaterMode(CanFrame frame){
  switch (frame.data[4]) {
    case 0:
      set_var_coolant_heater_mode("Off");
      break;
    case 1:
    set_var_coolant_heater_mode("On");
      break;
    case 2:
    set_var_coolant_heater_mode("Dgrd");
      break;
    case 3:
    set_var_coolant_heater_mode("Shut");
      break;
    case 4:
    set_var_coolant_heater_mode("Shrt");
      break;
    case 5:
    set_var_coolant_heater_mode("NRes");
      break;
    case 7:
    set_var_coolant_heater_mode("Stop");
      break;
  }

}

void updateBatteryVoltage(CanFrame frame){
  int16_t batVoltage = (frame.data[4] << 8) | frame.data[5];
  float batVoltageFloat = batVoltage *0.01;
  char buffer[8];
  sprintf(buffer, "%.2f v", batVoltageFloat);
  set_var_battery_voltage(buffer);

}

void updateBatteryCurrent(CanFrame frame){
  float batCurrent = (int8_t(frame.data[4]) * 256 + frame.data[5]) * 0.1;
  char buffer[10];
  sprintf(buffer, "%.1f A", batCurrent);
  set_var_battery_current(buffer);

}

void updateInteriorTemp(CanFrame frame){
  float interiorTemp = (frame.data[4] - 40) * 1.8 + 32;
  char buffer[8];
  sprintf(buffer, "%.1f °f", interiorTemp);
  set_var_interior_temperature(buffer);
}

void updateHeaterLoopTemp(CanFrame frame){
  float heaterLoopTemp = (int8_t(frame.data[4]) * 256 + frame.data[5])  * 1.8+32;
  char buffer[10];
  sprintf(buffer, "%.1f °f", heaterLoopTemp);
  set_var_heater_loop_temp(buffer);
}

