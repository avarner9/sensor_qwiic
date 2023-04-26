#include "stm32g030.h"

#include "i2c_sub_hw.h"


static uint8_t cur_addr = 0;

static bool addressed = false;
static bool read_mode = false;
static bool deselect_acknowledged = true;


void initialize_i2c_sub_hw(void)
{
    //SCL: pin 30 PB6: AF6 I2C1_SCL
    //SDA: pin 31 PB7: AF6 I2C1_SDA

    RCC_IOPENR |= 0x00000002; //enable GPIOBB
    RCC_IOPENR; //wait
    RCC_IOPENR; //wait
    GPIOB_AFRL |= 0x66000000; //set PB6 and PB7 to AF6
    GPIOB_OTYPER |= 0x000000C0; //set PB6 and PB7 to open drain mode
    GPIOB_PUPDR |= 0x00005000; //set PB6 and PB7 to have internal pullups (in case they are disconnected from the master momentarily)
    GPIOB_MODER |= 0x0000A000; //set PB6 and PB7 to AF

    RCC_APBENR1 |= 0x00200000; //enable clock to I2C1
    RCC_APBENR1; //wait
    RCC_APBENR1; //wait

    I2C1_CR1 |= 0x00080F00; //enable GCEN and DNF

    I2C1_CR2 |= 0x00000000; //nothing to set here

    i2c_sub_hw_set_addr(0x10);
    I2C1_TIMINGR = 0x00000000; //TODO: set this correctly, after we have set up the clock.

    I2C1_CR1 |= 0x00000001; //enable I2C1
}

void process_i2c_sub_hw(void)
{
    if (!addressed)
    {
        addressed = ((I2C1_ISR & 0x00000008) != 0);
        read_mode = ((I2C1_ISR & 0x00010000) != 0);
    }

    if (addressed)
    {
        bool bus_active = ((I2C1_ISR & 0x00008000) != 0);
        bool stop_bit = ((I2C1_ISR & 0x00000020) != 0);
        if (stop_bit || !bus_active)
        {
            addressed = false;
            read_mode = false;
            deselect_acknowledged = false;
        }
    }
}

void i2c_sub_hw_set_addr(uint8_t addr)
{
    cur_addr = addr;
    I2C1_OAR1 = 0; //disable own address
    I2C1_OAR1 = (0xFE & (cur_addr << 1)); //set new address
    I2C1_OAR1 |= 0x00008000; //enable own address
    //TODO: test how this works, in a sequential write where the master then writes a few bytes after this.
}

bool i2c_sub_hw_b_selected(void)
{
    if (!deselect_acknowledged)
    {
        deselect_acknowledged = true;
        return false;
    }
    return addressed;
}
bool i2c_sub_hw_b_read_mode(void)
{
    return read_mode;
}
bool i2c_sub_hw_b_has_unread_bytes(void)
{
    if (!addressed)
        return false;
    if (read_mode)
        return false;
    return ((I2C1_ISR & 0x00000004) != 0);
}
uint8_t i2c_sub_hw_get_byte(void)
{
    if (!i2c_sub_hw_b_has_unread_bytes())
        return 0;
    return I2C1_RXDR;
}
bool i2c_sub_hw_b_wants_byte(void)
{
    if (!addressed)
        return false;
    if (!read_mode)
        return false;
    return ((I2C1_ISR & 0x00000001) != 0);
}
void i2c_sub_hw_send_byte(uint8_t data)
{
    if (!i2c_sub_hw_b_wants_byte())
        return;
    I2C1_TXDR = data;
}
