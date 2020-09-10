#include "gpio_functions.h"

int main(void) {


	/*
	 * Demonstration of how the functions are used
	 * to blink on the blue LED of the STM32F4DISCOVERY
	 * board
	 */

	gpio_init(&GPIOD, 15);

	while (1) {
		gpio_write(&GPIOD, 15, 1);
		for (int i = 0; i < 500000; i++)
			;
		gpio_write(&GPIOD, 15, 0);

		for (int i = 0; i < 500000; i++)
			;
	}
}

