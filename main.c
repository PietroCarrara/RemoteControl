#include "wifi-util.h"
#include "graphics.h"
#include "input_util/input_util.h"

#include <pspdebug.h>
#include <pspmodulemgr.h>
#include <pspkernel.h>
#include <pspctrl.h>
#include <stdbool.h>

PSP_MODULE_INFO("Remote Controller", PSP_MODULE_USER, 0, 1);
// PSP_MAIN_THREAD_ATTR(0);

#define printf pspDebugScreenPrintf

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
	sceKernelExitGame();

	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);

	sceKernelSleepThreadCB();

	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

void handleInput() {
	
	while(true) {
		inputUpdate();

		if (inputIsButtonPressed(PSP_CTRL_NOTE)) {
			break;
		}

		if (inputIsButtonPressed(PSP_CTRL_CROSS)) {
			printf("\nX");
		}

		if (inputIsButtonPressed(PSP_CTRL_TRIANGLE)) {
			break;
		}
	}

}

void loadModules() {

	SceKernelLMOption option = {
		.size = sizeof(option),
		.mpidtext = (SceUID) 1, // SceUID mpid 1 = kernel partition
		.mpiddata = (SceUID) 1,
		.position = 0,
		.access = 1
	};

	printf("Loading module...\n");

	SceUID inpMod = sceKernelLoadModule("ms0:/PSP/GAME/RemoteControl/input_util.prx", 0, &option);

	if (inpMod < 0) {
		printf("Failed to load input_util.prx: code %x", inpMod);
		sceKernelDelayThread(1000000 * 5);
		sceKernelExitGame();
		return;
	}

	printf("Module Loaded!\nStarting Module...\n");

	/*
	SceModule* mod = sceKernelFindModuleByUID(inpMod);
	printf("mod %p\n", mod);
	if(mod != NULL)
	{
		printf("Attr %04X, Version %x.%x\n", mod->attribute, mod->version[0], mod->version[1]);
		printf("Name %s\n", mod->modname);
		printf("Text %08X, Size %08X, Data Size %08X\n", mod->text_addr, mod->text_size, mod->data_size);
		printf("Entry Addr %08X\n", mod->entry_addr);
		printf("Stub %p %08X, Ent %p %08X\n", mod->stub_top, mod->stub_size, mod->ent_top, mod->ent_size);
		int i;
		for(i = 0; i < mod->nsegment; i++)
		{
			printf("Segment[%d] %08X %08X\n", i, mod->segmentaddr[i], mod->segmentsize[i]);
		}
	}	
	*/

	SceKernelSMOption sOp = {
		.size = sizeof(sOp),
	};
	int status = 0;
	int res = sceKernelStartModule(inpMod, 0, NULL, &status, &sOp);
	if (res < 0) {
		printf("Failed to start input_util.prx: code %d", res);
		sceKernelDelayThread(1000000 * 5);
		sceKernelExitGame();
		return;
	}

	printf("Module started!\n");

	printf("Status of started module: %d", status);
}

int main()
{
	pspDebugScreenInit();

	// pspDebugInstallKprintfHandler(NULL);
	// pspDebugInstallErrorHandler(NULL);
	// pspDebugInstallStdoutHandler(pspDebugScreenPrintData);
	// pspSdkInstallNoPlainModuleCheckPatch();

	SetupCallbacks();

	printf("Callbacks prontos!");

	loadModules();

	inputInit();

	// It returns trash for now
	printf("The X is up...\n");
	while (inputIsButtonUp(PSP_CTRL_CROSS)) {
		inputUpdate();
		printf("Waiting for you to press the X\n");
	}

	// It returns trash for now
	printf("The X is down...\n");
	while (inputIsButtonDown(PSP_CTRL_CROSS)) {
		inputUpdate();
		printf("Waiting for you to release the X\n");
	}

	graphicsInit();

	// Connect to network
	do {
		if(wifiConnect()) {
			break;
		}
		graphicsClearScreen();
		printf("You weren't able to connect to a network.\n");
		printf("Do you wish to try again?\n");
		printf("X - Yes\n");
		printf("O - No\n");

		while(true) {
			inputUpdate();

			if (inputIsButtonPressed(PSP_CTRL_CROSS)) {
				break;
			}

			if (inputIsButtonPressed(PSP_CTRL_CIRCLE)) {
				sceKernelExitDeleteThread(0);
				return 0;
			}
		}

	} while (true);

	graphicsClearScreen();

	printf("You are connected!");

	handleInput();
	
	sceKernelExitGame();
	return 0;
}
