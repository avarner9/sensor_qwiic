#include <string.h>
#include "stm32g030.h"

#include "i2c_dom.h"


static uint8_t state = 0;
static uint8_t buffer[10];
static uint8_t data_length = 0;
static bool write_operation = false;
static uint8_t sub_addr = 0;
static uint8_t reg_addr = 0;


void initialize_i2c_dom(void)
{
    /* Pin assignments:
        p#  name    periph      signal
        22  PA11    I2C2_SCL    SCL
        23  PA12    I2C2_SDA    SDA
        17  PB2     GPIOB_P2    INT
    */

    RCC_IOPENR |= 0x00000003; //enable GPIOA and GPIOB
    RCC_IOPENR; //wait
    RCC_IOPENR;

    GPIOA_AFRH |= 0x00066000; //set PA11 and PA12 as AF6
    GPIOA_OTYPER |= 0x00001800; //set PA11 and PA12 output mode as open-drain
    GPIOA_MODER &= 0xFEBFFFFF; //set PA11 and PA12 as AF
    GPIOA_PUPDR |= 0x01400000; //set pull-up resistors on PA11 and PA12

    GPIOB_MODER &= 0xFFFFFCFF; //set PB2 as input

    RCC_APBENR1 |= 0x00400000; //enable I2C2
    RCC_APBENR1; //wait
    RCC_APBENR1;

    I2C2_CR1 |= 0x00000F00; //enable maximum filtering
    I2C2_TIMINGR |= 0xF0FFFFFF; //make the I2C as slow as possible
    I2C2_CR1 |= 0x00000001; //enable I2C2


    //TODO: consider moving the following initialization code to a new module
    nau7802_reset = 0x03;
    i2c_dom_write(0x2A, 0, &nau7802_reset, 1);
    while (i2c_dom_is_busy())
        process_i2c_dom();
    delay_ms(2);

    nau7802_digital_startup = 0x02;
    i2c_dom_write(0x2A, 0, &nau7802_digital_startup, 1);
    while (i2c_dom_is_busy())
        process_i2c_dom();
    delay_ms(2);

    uint8_t nau7802_registers[] = {
        0x06, //powerup digital and analog
        0x3F, //set LDO to 2.4V (min), and gain to 128 (max)
        0x70, //select channel 1, 320Hz sampling (max), no calibration
        };
    i2c_dom_write(0x2A, 0, nau7802_registers, sizeof(nau7802_registers));
    while (i2c_dom_is_busy())
        process_i2c_dom();
}
void process_i2c_dom(void)
{
    if (state == 1)
    {
        I2C2_CR2 = 0x00000000; //set modes up
        uint32_t write_length = 0;
        if (write_operation)
        {
            I2C2_CR2 |= 0x02000000; //automatic stop at end
            write_length = data_length + 1; //1 extra byte for reg addr
        }
        else
        {
            write_length = 1; //only 1 byte, for the reg addr
        }
        I2C2_CR2 |= (write_length << 16); //set number of bytes to transfer
        I2C2_CR2 |= (sub_addr << 1);

        I2C2_CR2 |= 0x00002000; //send start condition
        while ((I2C2_ISR & 0x00000012) == 0) //wait for start and addressing to complete
            ; //TODO: handle NACK

        I2C2_TXDR = reg_addr; //send register address
        while ((I2C2_ISR & 0x00000011) == 0) //TXE bit
            ; //TODO: handle NACK

        if (write_operation)
        {
            for (size_t i = 0; i < data_length; i++)
            {
                I2C2_TXDR = buffer[i];
                while ((I2C2_ISR & 0x00000011) == 0) //TXE bit
                    ; //TODO: handle NACK
            }
        }
        else
        {
            uint32_t i2c2_cr2 = 0x00000000; //set modes up
            i2c2_cr2 |= 0x00000400; //read mode
            i2c2_cr2 |= (data_length << 16); //set number of bytes to transfer
            i2c2_cr2 |= 0x02000000; //automatic stop at end
            i2c2_cr2 |= (sub_addr << 1);

            I2C2_CR2 = i2c2_cr2;

            I2C2_CR2 |= 0x00002000; //send re-start condition

            for (size_t i = 0; i < data_length; i++)
            {
                //TODO: handle NACK (can happen on address only)
                while ((I2C2_ISR & 0x00000004) == 0) //RXNE bit
                    ;
                buffer[i] = I2C2_RXDR;
            }
        }
        while ((I2C2_ISR & 0x00000020) == 0)
            ;
        state = 0;
        I2C2_CR1 &= 0xFFFFFFFE; //reset I2C2
        I2C2_CR1; //wait for reset
        I2C2_CR1;
        I2C2_CR1 |= 0x00000001; //enable I2C2
    }


    return;
/*

    switch (state)
    {
        case 0: //idle
        {
            break;
        }
        case 1: //queued, but not started yet
        {
            send start command
            state++;
            break;
        }
        case 2: //waiting for start signal to finish
        {
            if (start_signal_is_finished)
                state++;
            break;
        }
    }
    */
}

bool i2c_dom_is_busy(void)
{
    return (state != 0);
}
void i2c_dom_read(uint8_t sub_addr_, uint8_t reg_addr_, uint8_t num_bytes)
{
    if (i2c_dom_is_busy())
        return;
    sub_addr = sub_addr_ & 0x7F;
    reg_addr = reg_addr_;
    data_length = num_bytes;
    write_operation = false;
    state = 1;
}
void i2c_dom_write(uint8_t sub_addr_, uint8_t reg_addr_, const uint8_t * input, uint8_t num_bytes)
{
    if (i2c_dom_is_busy())
        return;
    if (num_bytes > sizeof(buffer))
        num_bytes = sizeof(buffer);
    sub_addr = sub_addr_ & 0x7F;
    reg_addr = reg_addr_;
    for (size_t i = 0; i < num_bytes; i++)
        buffer[i] = input[i];
    data_length = num_bytes;
    write_operation = true;
    state = 1;
}
void i2c_dom_get_data(uint8_t * output, size_t buffer_length)
{
    if (i2c_dom_is_busy())
        return;
    for (size_t i = 0; (i < data_length) && (i < buffer_length); i++)
        output[i] = buffer[i];
}
bool i2c_dom_get_int(void)
{
    return ((GPIOB_IDR & 0x00000004) == 0);
}
