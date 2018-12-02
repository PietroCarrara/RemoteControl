#include "input_util.h"

// Kernel module
PSP_MODULE_INFO("InputUtil", PSP_MODULE_USER, 1, 0); 
PSP_NO_CREATE_MAIN_THREAD();

SceCtrlData current, prev;

void inputUpdate() {
	prev = current;

	sceCtrlReadBufferPositive(&current, 1);
}

int inputIsButtonDown(enum PspCtrlButtons bt) {
	return current.Buttons & bt;
}

int inputIsButtonUp(enum PspCtrlButtons bt) {
	return !(current.Buttons & bt);
}

int inputIsButtonPressed(enum PspCtrlButtons bt) {
	// Has not been pressed before but is now
	return (!(prev.Buttons & bt)) && current.Buttons & bt;
}

int inputIsButtonReleased(enum PspCtrlButtons bt) {
	// Was pressed before but is not now
	return (!(current.Buttons & bt)) && prev.Buttons & bt;

}

int module_start(SceSize arg, void* argp) {
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

	return 0;
}

int module_stop(SceSize arg, void* argp) {
	return 0;
}
