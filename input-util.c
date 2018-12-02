#include "input-util.h"

static SceCtrlData current, prev;

void inputInit() {
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_DIGITAL);
}

void inputUpdate() {
	prev = current;

	sceCtrlReadBufferPositive(&current, 1);
}

int inputIsButtonDown(enum PspCtrlButtons bt) {
	return current.Buttons & bt;
}

int inputIsButtonUp(enum PspCtrlButtons bt) {
	return prev.Buttons & bt;
}

int inputIsButtonPressed(enum PspCtrlButtons bt) {
	// Has not been pressed before but is now
	return (!(prev.Buttons & bt)) && current.Buttons & bt;
}

int inputIsButtonReleased(enum PspCtrlButtons bt) {
	// Was pressed before but is not now
	return (!(current.Buttons & bt)) && prev.Buttons & bt;
}
