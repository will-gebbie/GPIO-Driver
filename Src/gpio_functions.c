#include "gpio_functions.h"

// Indices correspond to bit positions in peripheral registers
volatile uint32_t *const ports[NUMPORTS] = { &GPIOA, &GPIOB, &GPIOC, &GPIOD,
		&GPIOE, &GPIOF, &GPIOG, &GPIOH };

int getPortIndex(volatile uint32_t *port) {

	int index = BADPORT;
	// Identify which port was passed
	for (int i = 0; i < NUMPORTS; i++) {
		if (port == ports[i]) {
			index = i;
		}
	}

	// If the port wasn't in the list, exit program
	if (index == BADPORT) {
		printf("Invalid Port used.\n");
		exit(BADPORT);
	}

	return index;
}

void pinCheck(uint32_t pin) {
	if (pin < 0 || pin > (NUMPINS - 1)) {
		printf("Invalid Pin Number used.\n");
		exit(BADPIN);
	}
}


/*
 * This function sets up the clock and the mode to output
 * for the respective port and pin.
 */
void gpio_init(volatile uint32_t *port, uint32_t pin) {

	pinCheck(pin);

	int index = getPortIndex(port);

	// Enable Port Clock
	RCC_AHB1ENR &= ~(1 << index);
	RCC_AHB1ENR |= (1 << index);

	// Set mode of pin to output
	*port &= ~(3 << (pin * 2));
	*port |= (1 << (pin * 2));

}

void gpio_write(volatile uint32_t *port, volatile uint32_t pin, uint32_t value) {
	// Check port, pin, and value
	pinCheck(pin);
	getPortIndex(port); // <-- checks port validity
	if (value < 0 || value > 1) {
		printf("Invalid Value used.\n");
		exit(BADVALUE);
	}

	volatile uint32_t *pOutput =
			(volatile uint32_t*) (((volatile uint32_t) port) + ODR_OFFSET);

	// Set the Output Data Register to value for specified pin
	*pOutput &= ~(1 << pin);
	*pOutput |= (value << pin);

}

uint32_t gpio_read(volatile uint32_t *port, volatile uint32_t pin) {

	pinCheck(pin);
	getPortIndex(port);

	volatile uint32_t *pOutput =
			(volatile uint32_t*) (((volatile uint32_t) port) + ODR_OFFSET);

	return (*pOutput >> pin) & 0x1;
}
