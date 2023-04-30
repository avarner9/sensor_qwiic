#include "stm32g030.h"

#include "led.h"


void initialize_led(void)
{
    /*
    pin assignments:
    For the current prototype board:
    p#  name    periph      LED
    1   PB9     TIM17_CH1   blue
    13  ?       TIM16_CH1   red
    27  ?       TIM1_CH2    green

    for the next revision of board (not ordered yet)
    p#  name    periph      LED
    1   PB9     TIM17_CH1   blue
    19  ?       TIM1_CH2    red
    30  ?       TIM16_CH1N  green
    */

    RCC_IOPENR |= 0x00000002;
    GPIOB_MODER &= 0xFFF7FFFF;
    GPIOB_ODR &= 0xFFFFFDFF;
}


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
    if (duty >= 32768)
        GPIOB_ODR &= 0xFFFFFDFF;
    else
        GPIOB_ODR |= 0x00000200;
}
