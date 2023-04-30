#include "analog.h"
#include "eeprom.h"


static uint32_t cal_data[4];
static uint8_t cal_state = 0;


void initialize_analog(void)
{
    for (uint8_t i = 0; i < 4; i++)
        cal_data[i] = eeprom_get_long(0x10 + i * 4);
}
void process_analog(void)
{
}


bool analog_get_b(void)
{
    return false;
}
uint32_t analog_get_raw(void)
{
    return 0x800000;
}
uint32_t analog_get_derived(void)
{
    return 50000;
}
uint32_t analog_get_cal(uint8_t i)
{
    if (i > 4)
        return 0;
    return cal_data[i];
}
uint8_t analog_get_cal_state(void)
{
    return cal_state;
}
void analog_start_cal(uint8_t step)
{
    if (cal_state != 0)
        return;
    cal_state = step;
}

