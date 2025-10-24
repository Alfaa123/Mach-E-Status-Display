#include <ESP32-TWAI-CAN.hpp>
#include "screenVariables.h"
#include <Arduino.h>


void printDebugInfo(CanFrame frame);
void updateBatteryLevel (CanFrame frame);
void updatePrimaryMotorTorque(CanFrame frame);
void updateSecondaryMotorTorque(CanFrame frame);
void updateTorqueSplit();