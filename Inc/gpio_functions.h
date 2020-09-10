#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
// Define Peripheral Registers
#define RCC_AHB1ENR		*((volatile uint32_t*) 0x40023830 )
#define GPIOA			*((volatile uint32_t*) 0x40020000 )
#define GPIOB			*((volatile uint32_t*) 0x40020400 )
#define GPIOC			*((volatile uint32_t*) 0x40020800 )
#define GPIOD			*((volatile uint32_t*) 0x40020C00 )
#define GPIOE			*((volatile uint32_t*) 0x40021000 )
#define GPIOF			*((volatile uint32_t*) 0x40021400 )
#define GPIOG			*((volatile uint32_t*) 0x40021800 )
#define GPIOH			*((volatile uint32_t*) 0x40021C00 )
#define ODR_OFFSET		0x14
#define NUMPORTS		8
#define NUMPINS			16
#define BADPORT			-1
#define BADPIN			-2
#define BADVALUE		-3

extern volatile uint32_t *const ports[NUMPORTS];

int getPortIndex(volatile uint32_t *port);
void pinCheck(uint32_t pin);
void gpio_init(volatile uint32_t *port, uint32_t pin);
void gpio_write(volatile uint32_t *port, volatile uint32_t pin, uint32_t value);
uint32_t gpio_read(volatile uint32_t *port, volatile uint32_t pin);

