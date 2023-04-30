#include <stdbool.h>

#include "stm32g030.h"
#include "clock.h"



static void delay_1s_loop(void);



static bool clock_initialized = false;

void delay1s(void)
{
    if (!clock_initialized)
    {
        delay_1s_loop();
    }
    else
    {
        //TODO: use a proper timer
        uint32_t end_time = get_time_ms() + 1000;
        while (((int32_t)(get_time_ms() - end_time)) < 0)
            ;
    }
}

static void delay_1s_loop(void)
{
    volatile long x;
    for (x = 0; x < 1200000; x++)
        x;
}


void delay_ms(uint32_t t)
{
    uint32_t start_time = get_time_ms();
    while (t > 0)
    {
        if ((get_time_ms() - start_time) > 1)
        {
            start_time += 1;
            t--;
        }
    }
}

void initialize_clock(void)
{
    //Set flash to 2 wait states, to allow for faster CPU clock. Also enable all flash caching and prefetch.
    FLASH_ACR |= 0x00000302;
    while ((FLASH_ACR & 0x00000302) != 0x00000302)
        ;

    /*
    PLLRCLK (64MHz) is sysclock
    max sys clock is 64MHz
    hsi is fixed at 16mhz on startup

    pllpclk is 64MHz
    pllqclk is 64MHz

    VCO output is 128MHz. Maximum is 344MHz.

    ADC clock will be AHB/1 (64mhz). Thus skipping pllpclk. I'm not planning on using the ADC right now, though.

    rtcclk is unused.

    AHB is 64MHz
    APB1 is 64MHz
    APB2 is 64MHz
    TIMPCLK is APB/1=64mhz
    */

    //Note: the processor starts in "voltage range 1", and must stay in that range for 64MHz to work correctly.

    RCC_CFGR |= 0; //keep AHB and APB prescalers set to 1 (relative to sysclock) so 64MHz

    uint32_t rcc_pllcfgr = RCC_PLLCFGR & 0x0FC0808C; //grab initial reserved bits, so as not to change them
    rcc_pllcfgr |= 0x00000002; //set HSI (16MHz) as PLL input
    rcc_pllcfgr |= 0x00000010; //set PLL input divider to 2 (8MHz)
    rcc_pllcfgr |= 0x00001000; //set PLL multiplier to 16 (128MHz)
    rcc_pllcfgr |= 0x00030000; //set PLL P output to divide by 2 (64MHz)
    rcc_pllcfgr |= 0x30000000; //set PLL R output to divide by 2 (64MHz)
    RCC_PLLCFGR = rcc_pllcfgr;

    RCC_CR |= 0x01000000; //enable PLL
    while ((RCC_CR & 0x02000000) == 0) //wait for PLL
        ;

    RCC_CFGR |= 0x00000002; //use PLL as sys clock
    while ((RCC_CFGR & 0x00000038) != 0x00000010) //wait for sys clock to switch to PLL
        ;

    RCC_APBENR2 |= 0x00008000; //enable TIM14
    RCC_APBENR2;
    RCC_APBENR2;

    TIM14_PSC = 63999; //64MHz/64000=1kHz
    TIM14_CR1 |= 0x00000001; //start TIM14
    TIM14_EGR = 0x00000001; //apply prescaler now

    clock_initialized = true;
}

uint32_t get_time_ms(void)
{
    return TIM14_CNT;
}

/* Timer usage:
TIM1    PWM output for LED
TIM16   PWM output for LED
TIM17   PWM output for LED
TIM4    not present
TIM6    not present
TIM7    not present
TIM15   not present
TIM3    unused
TIM14   1ms timer
*/

