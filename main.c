#include "wifi-util.h"
#include "graphics.h"
#include "input-util.h"

#include <pspdebug.h>
#include <pspkernel.h>

// Remote controller, run as user, version 0.1
PSP_MODULE_INFO("Remote Controller", PSP_MODULE_USER, 0, 1);

// Define the main thread's attribute value (optional)
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

// Define printf, just to make typing easier
#define printf	pspDebugScreenPrintf

int main()
{
	// SetupCallbacks();
	graphicsInit();

	pspDebugScreenInit();

	// Connect to network
	bool success = false;
	do {
		success = wifiConnect();
	} while (!success);

	graphicsClearScreen();

	printf("You are connected!");
	
	sceKernelDelayThread(3000*1000); // 3s

	sceKernelExitGame();
	return 0;
}
