#include "chip.h"
#include "buttons.h"
#include "ledDriver.h"

int main(void) {

	LEDInit();

	Buttons_Init();

	while (1) {

		if (Buttons_Poll(1))
			LEDSet(false);

		else
			LEDSet(true);
	}
}
