#include "input_util.h"

// Kernel module
PSP_MODULE_INFO("InputUtil", 0x1000, 1, 0); 

SceCtrlData current, prev;

void inputInit() {
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_DIGITAL);
}

void inputUpdate() {
	// pspDebugScreenPrintf("Updated input!!!");

	prev = current;

	sceCtrlPeekBufferPositive(&current, 1);
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

int main(int argc, char **argv)
{
	sceKernelSleepThreadCB();

	return 0;
}
