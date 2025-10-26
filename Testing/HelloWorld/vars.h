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
    FLOW_GLOBAL_VARIABLE_PRIMARY_MOTOR_TEMP = 2,
    FLOW_GLOBAL_VARIABLE_SECONDARY_MOTOR_TEMP = 3,
    FLOW_GLOBAL_VARIABLE_HVB_THERMAL_MODE = 4,
    FLOW_GLOBAL_VARIABLE_HVB_TEMP = 5,
    FLOW_GLOBAL_VARIABLE_BATTERY_VOLTAGE = 6,
    FLOW_GLOBAL_VARIABLE_INTERIOR_TEMPERATURE = 7,
    FLOW_GLOBAL_VARIABLE_COOLANT_HEATER_POWER = 8,
    FLOW_GLOBAL_VARIABLE_COOLANT_HEATER_MODE = 9,
    FLOW_GLOBAL_VARIABLE_BATTERY_CURRENT = 10,
    FLOW_GLOBAL_VARIABLE_HEATER_LOOP_TEMP = 11
};

// Native global variables

extern const char *get_var_battery_level();
extern void set_var_battery_level(const char *value);
extern float get_var_battery_level_float();
extern void set_var_battery_level_float(float value);
extern const char *get_var_primary_motor_temp();
extern void set_var_primary_motor_temp(const char *value);
extern const char *get_var_secondary_motor_temp();
extern void set_var_secondary_motor_temp(const char *value);
extern const char *get_var_hvb_thermal_mode();
extern void set_var_hvb_thermal_mode(const char *value);
extern const char *get_var_hvb_temp();
extern void set_var_hvb_temp(const char *value);
extern const char *get_var_battery_voltage();
extern void set_var_battery_voltage(const char *value);
extern const char *get_var_interior_temperature();
extern void set_var_interior_temperature(const char *value);
extern const char *get_var_coolant_heater_power();
extern void set_var_coolant_heater_power(const char *value);
extern const char *get_var_coolant_heater_mode();
extern void set_var_coolant_heater_mode(const char *value);
extern const char *get_var_battery_current();
extern void set_var_battery_current(const char *value);
extern const char *get_var_heater_loop_temp();
extern void set_var_heater_loop_temp(const char *value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/