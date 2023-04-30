#include <stdbool.h>

#include "stm32g030.h"


void jump_to_bootloader(void)
{
    /*
    TODO:
    disable all interrupts (use primask 1)
    shut down all peripherals
    switch to HSI clock source
    shut down pll
    set stack pointer to system_memory[0];
    jump to system_memory[1];
    */
    while (true)
        ;
}


