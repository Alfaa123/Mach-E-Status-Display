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
    FLOW_GLOBAL_VARIABLE_RR_WHEELSPEED = 3
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


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/