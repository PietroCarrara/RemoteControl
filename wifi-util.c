// This code is almost a copy+paste from OSLib,
// an awesome library that I couldn't get to work :(

#include "wifi-util.h"

bool wifiConnect()
{
	// Load modules
	sceUtilityLoadModule(PSP_MODULE_NET_COMMON);
	sceUtilityLoadModule(PSP_MODULE_NET_INET);

	// Initialize modules
	sceNetInit(0x20000, 0x30, 0x1000, 0x30, 0x1000);
	sceNetInetInit();
	sceNetApctlInit(0x8000, 0x30);

	bool done = false;

	// Retrieve the system language
	int systemLanguage = 0;
	if (sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &systemLanguage) == PSP_SYSTEMPARAM_RETVAL_FAIL)
	{
		systemLanguage = PSP_SYSTEMPARAM_LANGUAGE_ENGLISH;
	}

	pspUtilityNetconfData data;
	memset(&data, 0, sizeof(data));
	data.base.size = sizeof(data);
	data.base.language = systemLanguage;

	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN, &data.base.buttonSwap);

	data.base.graphicsThread = 17;
	data.base.accessThread = 19;
	data.base.fontThread = 18;
	data.base.soundThread = 16;
	data.action = 3; // Connect to last used network

	struct pspUtilityNetconfAdhoc adhocparam;
	memset(&adhocparam, 0, sizeof(adhocparam));
	data.adhocparam = &adhocparam;

	done = (sceUtilityNetconfInitStart(&data) < 0);

	while (!done)
	{    
		switch (sceUtilityNetconfGetStatus())
		{
			case PSP_UTILITY_DIALOG_NONE:
				break;

			case PSP_UTILITY_DIALOG_INIT:
				// graphicDrawBackground(false, true);
				break;

			case PSP_UTILITY_DIALOG_VISIBLE:
				// graphicDrawBackground(false, true);
				sceUtilityNetconfUpdate(1);
				break;

			case PSP_UTILITY_DIALOG_QUIT:
				sceUtilityNetconfShutdownStart();
				break;

			case PSP_UTILITY_DIALOG_FINISHED:
				done = true;
				break;
		}

		sceDisplayWaitVblankStart();
		// sceGuSwapBuffers();
	}

	// Check for access point connection
	int state;
	sceNetApctlGetState(&state);

	return (state == PSP_NET_APCTL_STATE_GOT_IP);
}
