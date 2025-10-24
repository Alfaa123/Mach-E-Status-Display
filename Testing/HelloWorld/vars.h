#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations



// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_FL_WHEELSPEED = 0,
    FLOW_GLOBAL_VARIABLE_FR_WHEELSPEED = 1,
    FLOW_GLOBAL_VARIABLE_RL_WHEELSPEED = 2,
    FLOW_GLOBAL_VARIABLE_RR_WHEELSPEED = 3,
    FLOW_GLOBAL_VARIABLE_BATTERY_LEVEL = 4,
    FLOW_GLOBAL_VARIABLE_BATTERY_LEVEL_FLOAT = 5
};

// Native global variables

extern const char *get_var_fl_wheelspeed();
extern void set_var_fl_wheelspeed(const char *value);
extern const char *get_var_fr_wheelspeed();
extern void set_var_fr_wheelspeed(const char *value);
extern const char *get_var_rl_wheelspeed();
extern void set_var_rl_wheelspeed(const char *value);
extern const char *get_var_rr_wheelspeed();
extern void set_var_rr_wheelspeed(const char *value);
extern const char *get_var_battery_level();
extern void set_var_battery_level(const char *value);
extern float get_var_battery_level_float();
extern void set_var_battery_level_float(float value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/