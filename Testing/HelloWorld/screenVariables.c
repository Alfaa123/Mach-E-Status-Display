#include "vars.h"
#include <string.h>

char battery_level[7] = { 0 };
float battery_level_float;
char primary_motor_temp[10] = { 0 };
char secondary_motor_temp[10] = { 0 };
char hvb_thermal_mode[20] = { 0 };
char hvb_temp[8] = { 0 };
char battery_voltage[10] = { 0 };
char interior_temperature[10] = { 0 };
char coolant_heater_power[10] = { 0 };
char coolant_heater_mode[5] = { 0 };
char battery_current[10] = { 0 };
char heater_loop_temp[10] = { 0 };

const char *get_var_heater_loop_temp() {
    return heater_loop_temp;
}

void set_var_heater_loop_temp(const char *value) {
    strncpy(heater_loop_temp, value, sizeof(heater_loop_temp) / sizeof(char));
    heater_loop_temp[sizeof(heater_loop_temp) / sizeof(char) - 1] = 0;
}


const char *get_var_battery_current() {
    return battery_current;
}

void set_var_battery_current(const char *value) {
    strncpy(battery_current, value, sizeof(battery_current) / sizeof(char));
    battery_current[sizeof(battery_current) / sizeof(char) - 1] = 0;
}

const char *get_var_coolant_heater_mode() {
    return coolant_heater_mode;
}

void set_var_coolant_heater_mode(const char *value) {
    strncpy(coolant_heater_mode, value, sizeof(coolant_heater_mode) / sizeof(char));
    coolant_heater_mode[sizeof(coolant_heater_mode) / sizeof(char) - 1] = 0;
}

const char *get_var_coolant_heater_power() {
    return coolant_heater_power;
}

void set_var_coolant_heater_power(const char *value) {
    strncpy(coolant_heater_power, value, sizeof(coolant_heater_power) / sizeof(char));
    coolant_heater_power[sizeof(coolant_heater_power) / sizeof(char) - 1] = 0;
}

const char *get_var_interior_temperature() {
    return interior_temperature;
}

void set_var_interior_temperature(const char *value) {
    strncpy(interior_temperature, value, sizeof(interior_temperature) / sizeof(char));
    interior_temperature[sizeof(interior_temperature) / sizeof(char) - 1] = 0;
}

const char *get_var_battery_voltage() {
    return battery_voltage;
}

void set_var_battery_voltage(const char *value) {
    strncpy(battery_voltage, value, sizeof(battery_voltage) / sizeof(char));
    battery_voltage[sizeof(battery_voltage) / sizeof(char) - 1] = 0;
}

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

const char *get_var_secondary_motor_temp() {
    return secondary_motor_temp;
}

void set_var_secondary_motor_temp(const char *value) {
    strncpy(secondary_motor_temp, value, sizeof(secondary_motor_temp) / sizeof(char));
    secondary_motor_temp[sizeof(secondary_motor_temp) / sizeof(char) - 1] = 0;
}

const char *get_var_primary_motor_temp() {
    return primary_motor_temp;
}

void set_var_primary_motor_temp(const char *value) {
    strncpy(primary_motor_temp, value, sizeof(primary_motor_temp) / sizeof(char));
    primary_motor_temp[sizeof(primary_motor_temp) / sizeof(char) - 1] = 0;
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
