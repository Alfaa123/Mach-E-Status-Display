#include "vars.h"
#include <string.h>

char fl_wheelspeed[5] = { 0 };
char fr_wheelspeed[5] = { 0 };
char rl_wheelspeed[5] = { 0 };
char rr_wheelspeed[5] = { 0 };
char battery_level[7] = { 0 };
float battery_level_float;

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

const char *get_var_fl_wheelspeed() {
    return fl_wheelspeed;
}

void set_var_fl_wheelspeed(const char *value) {
    strncpy(fl_wheelspeed, value, sizeof(fl_wheelspeed) / sizeof(char));
    fl_wheelspeed[sizeof(fl_wheelspeed) / sizeof(char) - 1] = 0;
}


const char *get_var_fr_wheelspeed() {
    return fr_wheelspeed;
}

void set_var_fr_wheelspeed(const char *value) {
    strncpy(fr_wheelspeed, value, sizeof(fr_wheelspeed) / sizeof(char));
    fr_wheelspeed[sizeof(fr_wheelspeed) / sizeof(char) - 1] = 0;
}

const char *get_var_rl_wheelspeed() {
    return rl_wheelspeed;
}

void set_var_rl_wheelspeed(const char *value) {
    strncpy(rl_wheelspeed, value, sizeof(rl_wheelspeed) / sizeof(char));
    rl_wheelspeed[sizeof(rl_wheelspeed) / sizeof(char) - 1] = 0;
}


const char *get_var_rr_wheelspeed() {
    return rr_wheelspeed;
}

void set_var_rr_wheelspeed(const char *value) {
    strncpy(rr_wheelspeed, value, sizeof(rr_wheelspeed) / sizeof(char));
    rr_wheelspeed[sizeof(rr_wheelspeed) / sizeof(char) - 1] = 0;
}
