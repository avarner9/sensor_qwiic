#include "stm32g030.h"

#include "led.h"


void initialize_led(void)
{
    /* Pin assignments:
       For the current prototype board:
        p#  name    periph      LED
        1   PB9     TIM17_CH1   blue
        19  PA9     TIM1_CH2    red
        30  PB6     TIM16_CH1N  green

       For the next revision of board (not ordered yet)
        p#  name    periph      LED
        1   PB9     TIM17_CH1   blue
        13  PA6     TIM16_CH1   red
        27  PB3     TIM1_CH2    green
    */

    RCC_IOPENR |= 0x00000002; //enable GPIOB
    RCC_IOPENR; //wait
    RCC_IOPENR; //wait
    GPIOB_AFRH |= 0x00000020; //set PB9 to AF2 (TIM17_CH1)
    GPIOB_MODER &= 0xFFFBFFFF; //set PB9 to AF mode
    GPIOB_MODER |= 0x00080000; //set PB9 to AF mode

    RCC_APBENR2 |= 0x00060800; //enable TIM1, TIM16, and TIM17
    RCC_APBENR2; //wait
    RCC_APBENR2; //wait

    TIM17_CCR1 = 63000;
    TIM17_CCMR1 |= 0x00000078;
    TIM17_CCER |= 0x00000007;
    TIM17_BDTR |= 0x00008000; //enable MOE (main output enable)
    TIM17_EGR |= 0x00000001; //generate update
    TIM17_CR1 |= 0x00000001; //enable counter
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
    TIM17_CCR1 = 65535 - duty;
}
