#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "stm32g030.h"

#include "clock.h"
//#include "uart_dma.h"
#include "i2c_dom.h"
#include "i2c_sub.h"
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
    //initialize_i2c_sub();
    initialize_i2c_dom();
    initialize_analog();

    bool i2c_read_active = false;

    //uint16_t t_origin = get_time_ms();
    while (true)
    {
        /*
        uint16_t dt = get_time_ms() - t_origin;
        if (dt > 2000)
        {
            t_origin += 2000;
            dt -= 2000;
        }
        int32_t pwm = dt;
        pwm *= 65535;
        pwm /= 2000;
        pwm = 65535 - pwm;
        if (pwm < 0)
            pwm = 0;
        if (pwm > 65535)
            pwm = 65535;
        led_set_pwm_b(pwm);*/

        if ((!i2c_dom_is_busy()) && (i2c_dom_get_int()))
        {
            i2c_dom_read(0x2A, 0x12, 3);
            i2c_read_active = true;
        }
        if (i2c_read_active && (!i2c_dom_is_busy()))
        {
            uint32_t result = 0;
            i2c_dom_get_data((uint8_t *)&result, 3);
            led_set_pwm_b(result / 256);
            i2c_read_active = false;
        }

        //process_dma_uart();
        //process_i2c_sub();
        process_i2c_dom();
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
