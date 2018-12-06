#ifndef REMOTE_H
#define REMOTE_H

#include <pspsdk.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pspctrl.h>
#include <psphttp.h>
#include <pspnet.h>
#include <pspnet_inet.h>
#include <psputility_netmodules.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/socket.h>

#ifndef SO_NONBLOCK
#define SO_NONBLOCK 0x1009
#endif

bool remoteInit(in_addr_t host, uint16_t port);
bool remoteSetState(enum PspCtrlButtons bt, bool isDown);
bool remoteSetValue(char* stick, unsigned char val);

#endif
