#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "stm32g030.h"

#include "clock.h"
//#include "uart_dma.h"
//#include "i2c_dom.h"
//#include "i2c_sub.h"
#include "led.h"
#include "analog.h"


int main(void)
{
    delay1s();
    delay1s();
    delay1s();
    delay1s();
    delay1s();

    initialize_led();
    initialize_clock();
    //initialize_dma_uart();
    initialize_analog();

    //initialize_i2c_sub();
    //initialize_i2c_dom();

    while (true)
    {
        delay1s();
        led_set_pwm_b(65535);
        delay1s();
        led_set_pwm_b(0);
        //process_dma_uart();
        //process_i2c_sub();
        //process_i2c_dom();
        process_analog();
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
