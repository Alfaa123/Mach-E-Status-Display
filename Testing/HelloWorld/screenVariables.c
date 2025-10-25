#include "vars.h"
#include <string.h>

char battery_level[7] = { 0 };
float battery_level_float;
float torque_split;
char primary_motor_torque[10] = { 0 };
char secondary_motor_torque[10] = { 0 };
char hvb_thermal_mode[20] = { 0 };
char hvb_temp[8] = { 0 };

const char *get_var_hvb_temp() {
    return hvb_temp;
}

void set_var_hvb_temp(const char *value) {
    strncpy(hvb_temp, value, sizeof(hvb_temp) / sizeof(char));
    hvb_temp[sizeof(hvb_temp) / sizeof(char) - 1] = 0;
}

const char *get_var_hvb_thermal_mode() {
    return hvb_thermal_mode;
}

void set_var_hvb_thermal_mode(const char *value) {
    strncpy(hvb_thermal_mode, value, sizeof(hvb_thermal_mode) / sizeof(char));
    hvb_thermal_mode[sizeof(hvb_thermal_mode) / sizeof(char) - 1] = 0;
}

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
