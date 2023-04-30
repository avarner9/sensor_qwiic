#include <stdint.h>


void jump_to_bootloader(void);


//incomplete

#define FLASH_ACR     (*(volatile uint32_t *)0x40022000)

//complete
#define RCC_CR        (*(volatile uint32_t *)0x40021000)
#define RCC_ICSCR     (*(volatile uint32_t *)0x40021004)
#define RCC_CFGR      (*(volatile uint32_t *)0x40021008)
#define RCC_PLLCFGR   (*(volatile uint32_t *)0x4002100C)
//reserved            (*(volatile uint32_t *)0x40021010)
//reserved            (*(volatile uint32_t *)0x40021014)
#define RCC_CIER      (*(volatile uint32_t *)0x40021018)
#define RCC_CIFR      (*(volatile uint32_t *)0x4002101C)
#define RCC_CICR      (*(volatile uint32_t *)0x40021020)
#define RCC_IOPRSTR   (*(volatile uint32_t *)0x40021024)
#define RCC_AHBRSTR   (*(volatile uint32_t *)0x40021028)
#define RCC_APBRSTR1  (*(volatile uint32_t *)0x4002102C)
#define RCC_APBRSTR2  (*(volatile uint32_t *)0x40021030)
#define RCC_IOPENR    (*(volatile uint32_t *)0x40021034)
#define RCC_AHBENR    (*(volatile uint32_t *)0x40021038)
#define RCC_APBENR1   (*(volatile uint32_t *)0x4002103C)
#define RCC_APBENR2   (*(volatile uint32_t *)0x40021040)
#define RCC_IOPSMENR  (*(volatile uint32_t *)0x40021044)
#define RCC_AHBSMENR  (*(volatile uint32_t *)0x40021048)
#define RCC_APBSMENR1 (*(volatile uint32_t *)0x4002104C)
#define RCC_APBSMENR2 (*(volatile uint32_t *)0x40021050)
#define RCC_CCIPR     (*(volatile uint32_t *)0x40021054)
#define RCC_CCIPR2    (*(volatile uint32_t *)0x40021058)
#define RCC_BDCR      (*(volatile uint32_t *)0x4002105C)
#define RCC_CSR       (*(volatile uint32_t *)0x40021060)

//complete
#define GPIOB_MODER   (*(volatile uint32_t *)0x50000400)
#define GPIOB_OTYPER  (*(volatile uint32_t *)0x50000404)
#define GPIOB_OSPEEDR (*(volatile uint32_t *)0x50000408)
#define GPIOB_PUPDR   (*(volatile uint32_t *)0x5000040C)
#define GPIOB_IDR     (*(volatile uint32_t *)0x50000410)
#define GPIOB_ODR     (*(volatile uint32_t *)0x50000414)
#define GPIOB_BSRR    (*(volatile uint32_t *)0x50000418)
#define GPIOB_LCKR    (*(volatile uint32_t *)0x5000041C)
#define GPIOB_AFRL    (*(volatile uint32_t *)0x50000420)
#define GPIOB_AFRH    (*(volatile uint32_t *)0x50000424)
#define GPIOB_BRR     (*(volatile uint32_t *)0x50000428)

//complete
#define I2C1_CR1      (*(volatile uint32_t *)0x40005400)
#define I2C1_CR2      (*(volatile uint32_t *)0x40005404)
#define I2C1_OAR1     (*(volatile uint32_t *)0x40005408)
#define I2C1_OAR2     (*(volatile uint32_t *)0x4000540C)
#define I2C1_TIMINGR  (*(volatile uint32_t *)0x40005410)
#define I2C1_TIMEOUTR (*(volatile uint32_t *)0x40005414)
#define I2C1_ISR      (*(volatile uint32_t *)0x40005418)
#define I2C1_ICR      (*(volatile uint32_t *)0x4000541C)
#define I2C1_PECR     (*(volatile uint32_t *)0x40005420)
#define I2C1_RXDR     (*(volatile uint32_t *)0x40005424)
#define I2C1_TXDR     (*(volatile uint32_t *)0x40005428)

//incomplete
#define TIM14_CR1     (*(volatile uint32_t *)0x40002000)
#define TIM14_EGR     (*(volatile uint32_t *)0x40002014)
#define TIM14_CNT     (*(volatile uint32_t *)0x40002024)
#define TIM14_PSC     (*(volatile uint32_t *)0x40002028)
