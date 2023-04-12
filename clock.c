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
        uint32_t end_time = get_time_us() + 1000000;
        while (((int32_t)(get_time_us() - end_time)) < 0)
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
    uint32_t start_time = get_time_us();
    while (t > 0)
    {
        if ((get_time_us() - start_time) > 1000)
        {
            start_time += 1000;
            t--;
        }
    }
}

void initialize_clock(void)
{
#if 0
// the following code is copied directly from the ddrcontroller project. it needs to be rewritten for the STM32G030 .

    //Set flash to 4 wait states, to allow for faster CPU clock. Also enable all flash caching and prefetch.
    FLASH_ACR = 0x00000704;
    

    //set APB2 prescaler to 16, relative to AHB (9MHz)
    RCC_CFGR |= 0x0000E000;
    //set APB1 prescaler to 16, relative to AHB (9MHz)
    RCC_CFGR |= 0x00001C00;



    //set AHB prescaler to 1, relative to system clock (144MHz)
    RCC_CFGR = (RCC_CFGR & 0xFFFFFF0F);

    //enable external crystal oscillator (12MHz)
    RCC_CR |= 0x00010000;
    //wait for the external crystal oscillator
    while ((RCC_CR & 0x00020000) == 0)
        ;

    //switch system clock to the external crystal oscillator (12MHz)
    RCC_CFGR = (RCC_CFGR & 0xFFFFFFFC) | 0x00000001;
    //wait for the system clock to change
    while ((RCC_CFGR & 0x0000000C) != 0x00000004)
        ;

    //set PLL USB post-divider to 6 (48MHz)
    RCC_PLLCFGR = (RCC_PLLCFGR & 0xF0FFFFFF) | 0x06000000;
    //set PLL input clock to HSE (12MHz crystal oscillator)
    RCC_PLLCFGR |= 0x00400000;
    //set PLL main system clock post divider to 2 (144MHz)
    RCC_PLLCFGR = (RCC_PLLCFGR & 0xFFFCFFFF);
    //set PLL multiplier to 144 (288MHz)
    RCC_PLLCFGR = (RCC_PLLCFGR & 0xFFFF803F) | (((uint32_t)144) << 6);
    //set PLL pre-divider to 6 (2MHz)
    RCC_PLLCFGR = (RCC_PLLCFGR & 0xFFFFFFC0) | ((uint32_t)6);

    //wait a bit
    RCC_CR;
    RCC_CR;
    RCC_CR;
    RCC_CR;
    RCC_CR;
    RCC_CR;
    RCC_CR;

    //enable the PLL (72MHz/144MHz/36MHz)
    RCC_CR |= 0x01000000;
    //wait for the PLL
    while ((RCC_CR & 0x02000000) == 0)
        ;
    //switch system clock to the PLL
    RCC_CFGR = (RCC_CFGR & 0xFFFFFFFC) | 0x00000002;
    //wait for the system clock to change
    while ((RCC_CFGR & 0x0000000C) != 0x00000008)
        ;

/*
    //shut off the HSI 16MHz internal oscillator
    RCC_CR = (RCC_CR & 0xFFFFFFFE);
    //wait for HSI to turn off
    while ((RCC_CR & 0xFFFFFFFD) != 0)
        ;
*/

    //enable TIM2
    RCC_APB1ENR |= 0x00000001;
    //divide APB1*2 by 18 to get 1MHz
    TIM2_PSC = 17;
    //start TIM2
    TIM2_CR1 |= 0x00000001;
    TIM2_EGR = 0x00000001;

    clock_initialized = true;
#endif
}

uint32_t get_time_us(void)
{
    return 0; //TODO
    //return TIM2_CNT;
}

