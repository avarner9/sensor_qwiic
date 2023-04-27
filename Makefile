#C_OBJECTS=uart.o newlib_helpers.o uart_dma.o i2c_dom.o analog.o eeprom.o
C_OBJECTS=start.o main.o clock.o i2c_sub.o i2c_sub_hw.o
AS_OBJECTS=

CC=arm-none-eabi-gcc
#CFLAGS=-mcpu=cortex-m0 -mthumb -Wall -Wextra --std=gnu99 -nostartfiles
CFLAGS=-mcpu=cortex-m0 -mthumb -Wall -Wextra --std=gnu99
LD=arm-none-eabi-ld
LDFLAGS=-T stm32g030.ld -nostartfiles
AS=arm-none-eabi-as
ASFLAGS=-mthumb


.PHONY : default install install_i2c

default : sensor_qwiic.bin


install : sensor_qwiic.bin
	openocd -f openocd.cfg -c 'init' -c 'halt' -c 'flash write_image erase ./sensor_qwiic.bin 0x08000000' -c 'exit'
#TODO: set option byte 0x1FFF7800 to 0xDEFFE1AA (default is 0xDEFFE1AA) . This enables the boot0 pin functionality.

install_i2c : sensor_qwiic.hex
	false
#TODO: set option byte 0x1FFF7800 to 0xDEFFE1AA (default is 0xDEFFE1AA) . This enables the boot0 pin functionality.
#TODO: set up i2c bootloader programmer here.


sensor_qwiic.bin : sensor_qwiic.hex
	arm-none-eabi-objcopy -I ihex sensor_qwiic.hex --only-section='*' -O binary sensor_qwiic.bin

sensor_qwiic.hex : sensor_qwiic.elf
	arm-none-eabi-objcopy sensor_qwiic.elf -O ihex sensor_qwiic.hex

sensor_qwiic.elf : $(C_OBJECTS) $(AS_OBJECTS)
#	$(LD) $(LDFLAGS) $(C_OBJECTS) $(AS_OBJECTS) -o sensor_qwiic.elf
	$(CC) $(CFLAGS) $(LDFLAGS) $(C_OBJECTS) $(AS_OBJECTS) -o sensor_qwiic.elf


clean :
	@touch dummy.o dummy.elf dummy.hex dummy.bin
	rm *.o *.elf *.hex *.bin

install-clean :
	dfu-util -d 0483:df11 -a 0 -D /dev/null

