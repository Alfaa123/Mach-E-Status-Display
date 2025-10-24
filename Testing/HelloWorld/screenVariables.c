#include "vars.h"
#include <string.h>

char battery_level[7] = { 0 };
float battery_level_float;
float torque_split;
char primary_motor_torque[7] = { 0 };
char secondary_motor_torque[7] = { 0 };

const char *get_var_secondary_motor_torque() {
    return secondary_motor_torque;
}

void set_var_secondary_motor_torque(const char *value) {
    strncpy(secondary_motor_torque, value, sizeof(secondary_motor_torque) / sizeof(char));
    secondary_motor_torque[sizeof(secondary_motor_torque) / sizeof(char) - 1] = 0;
}

const char *get_var_primary_motor_torque() {
    return primary_motor_torque;
}

void set_var_primary_motor_torque(const char *value) {
    strncpy(primary_motor_torque, value, sizeof(primary_motor_torque) / sizeof(char));
    primary_motor_torque[sizeof(primary_motor_torque) / sizeof(char) - 1] = 0;
}

float get_var_torque_split() {
    return torque_split;
}

void set_var_torque_split(float value) {
    torque_split = value;
}

float get_var_battery_level_float() {
    return battery_level_float;
}

void set_var_battery_level_float(float value) {
    battery_level_float = value;
}

const char *get_var_battery_level() {
    return battery_level;
}

void set_var_battery_level(const char *value) {
    strncpy(battery_level, value, sizeof(battery_level) / sizeof(char));
    battery_level[sizeof(battery_level) / sizeof(char) - 1] = 0;
}
