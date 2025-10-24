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
    FLOW_GLOBAL_VARIABLE_BATTERY_LEVEL = 0,
    FLOW_GLOBAL_VARIABLE_BATTERY_LEVEL_FLOAT = 1,
    FLOW_GLOBAL_VARIABLE_PRIMARY_MOTOR_TORQUE = 2,
    FLOW_GLOBAL_VARIABLE_SECONDARY_MOTOR_TORQUE = 3,
    FLOW_GLOBAL_VARIABLE_TORQUE_SPLIT = 4
};

// Native global variables

extern const char *get_var_battery_level();
extern void set_var_battery_level(const char *value);
extern float get_var_battery_level_float();
extern void set_var_battery_level_float(float value);
extern const char *get_var_primary_motor_torque();
extern void set_var_primary_motor_torque(const char *value);
extern const char *get_var_secondary_motor_torque();
extern void set_var_secondary_motor_torque(const char *value);
extern float get_var_torque_split();
extern void set_var_torque_split(float value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/