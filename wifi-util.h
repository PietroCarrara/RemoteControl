#ifndef WIFI_UTIL_H
#define WIFI_UTIL_H

#include <pspdisplay.h>
#include <pspkernel.h>
#include <pspnet.h>
#include <pspnet_apctl.h>
#include <pspnet_inet.h>
#include <psputility.h>
#include <psputility_netmodules.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CONFIGS 20

typedef struct {
	int id;	
	char name[128];
	char IP[128];

} NetConfigData;

// Connects to an network profile
// return true on success
bool wifiConnect();

#endif
