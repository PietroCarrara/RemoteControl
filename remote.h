#ifndef REMOTE_H
#define REMOTE_H

#include <pspsdk.h>
#include <pspctrl.h>
#include <psphttp.h>
#include <stdbool.h>
#include <psputility_netmodules.h>
#include <stdio.h>

bool remoteInit(char* host, unsigned short port);
bool remoteSetState(enum PspCtrlButtons bt, bool isDown);
bool setValue(char* stick, unsigned char val);

#endif
