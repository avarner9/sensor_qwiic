C_OBJECTS=start.o main.o clock.o i2c.o uart.o newlib_helpers.o uart_dma.o sensor_qwiic.o
AS_OBJECTS=

CC=arm-none-eabi-gcc
#CFLAGS=-mcpu=cortex-m4 -mthumb -Wall -Wextra --std=gnu99 -nostartfiles
CFLAGS=-mcpu=cortex-m4 -mthumb -Wall -Wextra --std=gnu99
LD=arm-none-eabi-ld
LDFLAGS=-T stm32f405.ld -nostartfiles
AS=arm-none-eabi-as
ASFLAGS=-mthumb




sensor_qwiic.bin : ddrcontroller.hex
	arm-none-eabi-objcopy -I ihex sensor_qwiic.hex --only-section='*' -O binary ddrcontroller.bin

install : sensor_qwiic.bin
	dfu-util -d 0483:df11 -a 0 -s 0x08000000 -D ./sensor_qwiic.bin

sensor_qwiic.hex : ddrcontroller.elf
	arm-none-eabi-objcopy sensor_qwiic.elf -O ihex ddrcontroller.hex

sensor_qwiic.elf : $(C_OBJECTS) $(AS_OBJECTS)
#	$(LD) $(LDFLAGS) $(C_OBJECTS) $(AS_OBJECTS) -o sensor_qwiic.elf
	$(CC) $(CFLAGS) $(LDFLAGS) $(C_OBJECTS) $(AS_OBJECTS) -o sensor_qwiic.elf




clean :
	@touch dummy.o dummy.elf dummy.hex dummy.bin
	rm *.o *.elf *.hex *.bin

install-clean :
	dfu-util -d 0483:df11 -a 0 -D /dev/null

