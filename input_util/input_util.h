#ifndef INPUT_UTIL_H
#define INPUT_UTIL_H

#include <pspctrl.h>
#include <pspsdk.h>

void inputInit();
void inputUpdate();

int inputIsButtonDown(enum PspCtrlButtons bt);
int inputIsButtonUp(enum PspCtrlButtons bt);
int inputIsButtonPressed(enum PspCtrlButtons bt);
int inputIsButtonReleased(enum PspCtrlButtons bt);

#endif
