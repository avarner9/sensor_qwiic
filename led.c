#include "led.h"


void led_set_digital(uint8_t d)
{
    if ((d & 0x04) != 0)
        led_set_pwm_r(UINT16_MAX);
    else
        led_set_pwm_r(0);

    if ((d & 0x02) != 0)
        led_set_pwm_g(UINT16_MAX);
    else
        led_set_pwm_g(0);

    if ((d & 0x01) != 0)
        led_set_pwm_b(UINT16_MAX);
    else
        led_set_pwm_b(0);
}
void led_set_pwm_r(uint16_t duty)
{
}
void led_set_pwm_g(uint16_t duty)
{
}
void led_set_pwm_b(uint16_t duty)
{
}

