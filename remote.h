#ifndef REMOTE_H
#define REMOTE_H

#include <pspsdk.h>
#include <pspctrl.h>
#include <psphttp.h>
#include <stdbool.h>
#include <psputility_netmodules.h>

const char* BUTTON_TO_STRING(enum PspCtrlButtons bt);
bool remoteInit(char* host, unsigned short port);

#endif
