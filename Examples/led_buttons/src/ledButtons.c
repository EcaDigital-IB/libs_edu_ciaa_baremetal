#include "chip.h"
#include "buttons.h"
#include "ledDriver.h"

int main(void) {

	LEDInit();

	Buttons_Init();

	while (1) {

		if (Buttons_Poll(BUTTONS_SW1))
			LEDSet(false);

		else
			LEDSet(true);
	}
}
