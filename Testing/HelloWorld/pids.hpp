#include <ESP32-TWAI-CAN.hpp>
#include "screenVariables.h"
#include <Arduino.h>


void printDebugInfo(CanFrame frame);
void updateBatteryLevel (CanFrame frame);
void updateHVBTemp(CanFrame frame);
void updateHVBThermalMode(CanFrame frame);
void updatePrimaryMotortemp(CanFrame frame);
void updateSecondaryMotortemp(CanFrame frame);
void updateCoolantHeaterPower(CanFrame frame);
void updateCoolantHeaterMode(CanFrame frame);
void updateBatteryVoltage(CanFrame frame);
void updateBatteryCurrent(CanFrame frame);
void updateInteriorTemp(CanFrame frame);
void updateHeaterLoopTemp(CanFrame frame);