#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "stm32g030.h"

#include "clock.h"
//#include "uart_dma.h"
//#include "i2c_dom.h"
//#include "i2c_sub.h"


int main(void)
{
    initialize_clock();
    //initialize_dma_uart();

    /*
    pb9, aka tim17_ch1, aka pin 1 on the lqft32 package, is the blue led. set it low to turn it on.
    */

    RCC_IOPENR |= 0x00000002;
    GPIOB_MODER |= 0x00040000;
    GPIOB_ODR &= 0xFFFFFDFF;

    //initialize_i2c_sub();
    //initialize_i2c_dom();

    while (true)
    {
        delay1s();
        GPIOB_ODR &= 0xFFFFFDFF;
        delay1s();
        GPIOB_ODR |= 0x00000200;
        //process_dma_uart();
        //process_i2c_sub();
        //process_i2c_dom();
    }
}


void * memset(void * ptr1, int c, size_t length)
{
    uint8_t * ptr2 = ptr1;
    for (size_t i = 0; i < length; i++)
        ptr2[i] = c;
    return ptr1;
}

void * memcpy(void * dst, const void * src, size_t length)
{
    uint8_t * dst2 = dst;
    const uint8_t * src2 = src;
    for (size_t i = 0; i < length; i++)
        dst2[i] = src2[i];
    return dst;
}
