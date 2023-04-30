#include <stdbool.h>
#include <stdint.h>


void initialize_analog(void);
void process_analog(void);


bool analog_get_b(void);
uint32_t analog_get_raw(void);
uint32_t analog_get_derived(void);
uint32_t analog_get_cal(uint8_t i);
uint8_t analog_get_cal_state(void);
void analog_start_cal(uint8_t step);

