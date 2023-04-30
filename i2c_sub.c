//#include <string.h>
#include "stm32g030.h"

#include "clock.h"
#include "i2c_sub.h"
#include "i2c_sub_hw.h"
#include "eeprom.h"
#include "analog.h"
#include "led.h"


static uint8_t reg_num = 0;
static bool reg_num_set = false;
static uint8_t bitfield = 0;


static uint8_t i2c_sub_read_register(uint8_t n);
static void i2c_sub_write_register(uint8_t n, uint8_t data);


void initialize_i2c_sub(void)
{
    initialize_i2c_sub_hw();
    i2c_sub_hw_set_addr(eeprom_get(0x33));
    reg_num = 0;
    reg_num_set = false;
    bitfield = eeprom_get(0x32);
}

void process_i2c_sub(void)
{
    process_i2c_sub_hw();
    if (!i2c_sub_hw_b_selected())
    {
        reg_num = 0;
        reg_num_set = false;
    }
    else
    {
        if (i2c_sub_hw_b_read_mode())
        {
            if (i2c_sub_hw_b_wants_byte())
            {
                i2c_sub_hw_send_byte(i2c_sub_read_register(reg_num));
                reg_num++;
            }
        }
        else
        {
            if (i2c_sub_hw_b_has_unread_bytes())
            {
                if (!reg_num_set)
                {
                    reg_num = i2c_sub_hw_get_byte();
                    reg_num_set = true;
                }
                else
                {
                    i2c_sub_write_register(reg_num, i2c_sub_hw_get_byte());
                    reg_num++;
                }
            }
        }
    }
}

static uint8_t i2c_sub_read_register(uint8_t n)
{
    static uint32_t cache = 0;
    switch (n)
    {
        case 0x00: //bitfield
            if (analog_get_b())
                return bitfield;
            else
                return 0xFF;
        case 0x01: //errors
            return 0;

        case 0x04: //derived analog
            cache = analog_get_derived();
            return cache & 0xFF;
        case 0x05: return (cache >>  8) & 0xFF;
        case 0x06: return (cache >> 16) & 0xFF;
        case 0x07: return (cache >> 24) & 0xFF;

        case 0x08: //raw analog
            cache = analog_get_raw();
            return cache & 0xFF;
        case 0x09: return (cache >>  8) & 0xFF;
        case 0x0A: return (cache >> 16) & 0xFF;
        case 0x0B: return (cache >> 24) & 0xFF;

        case 0x10: //cal 0: adc val with neutral load cell -- no weight, no strain relief
            cache = analog_get_cal(0);
            return cache & 0xFF;
        case 0x11: return (cache >>  8) & 0xFF;
        case 0x12: return (cache >> 16) & 0xFF;
        case 0x13: return (cache >> 24) & 0xFF;

        case 0x14: //cal 1: adc val with reference weight 1 on load cell, and no strain relief
            cache = analog_get_cal(1);
            return cache & 0xFF;
        case 0x15: return (cache >>  8) & 0xFF;
        case 0x16: return (cache >> 16) & 0xFF;
        case 0x17: return (cache >> 24) & 0xFF;

        case 0x18: //cal 2: adc val with strain relief applied, but no weight
            cache = analog_get_cal(2);
            return cache & 0xFF;
        case 0x19: return (cache >>  8) & 0xFF;
        case 0x1A: return (cache >> 16) & 0xFF;
        case 0x1B: return (cache >> 24) & 0xFF;

        case 0x1C: //cal 3: adc val with strain relief applied, and reference weight 2 on load cell
            cache = analog_get_cal(3);
            return cache & 0xFF;
        case 0x1D: return (cache >>  8) & 0xFF;
        case 0x1E: return (cache >> 16) & 0xFF;
        case 0x1F: return (cache >> 24) & 0xFF;

        //0x20 - 0x2F reserved for further calibration parameters

        case 0x30: //calibration state
            return analog_get_cal_state();
        case 0x31: //programming mode
            return 0;
        case 0x32: //bitfield
            return bitfield;
        case 0x33: //i2c addr
            return eeprom_get(0x33);

        default:
        {
            return 0;
        }
    }
}

static void i2c_sub_write_register(uint8_t n, uint8_t data)
{
    switch (n)
    {
        case 0x30: //calibration state
            analog_start_cal(data);
            break;
        case 0x31: //programming mode
            if (data == 1)
                jump_to_bootloader();
            break;
        case 0x32: //bitfield
            bitfield = n;
            break;
        case 0x33: //i2c addr
            eeprom_set(0x33, data);
            i2c_sub_hw_set_addr(data);
            break;
        case 0x40: //LED digital
            led_set_digital(data);
            break;
        case 0x41: //LED R
            led_set_pwm_r(data * 256);
            break;
        case 0x42: //LED G
            led_set_pwm_g(data * 256);
            break;
        case 0x43: //LED B
            led_set_pwm_b(data * 256);
            break;
    }
}

