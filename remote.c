#include "remote.h"

static int connectionID;

// Well... I couldn't think of any better way of doing this ;)
const char* BUTTON_TO_STRING(enum PspCtrlButtons bt) {
	switch(bt) {
		case PSP_CTRL_SELECT:
			return "SELECT";
		case PSP_CTRL_START:
			return "START";
		case PSP_CTRL_UP:
			return "UP";
		case PSP_CTRL_RIGHT:
			return "RIGHT";
		case PSP_CTRL_DOWN:
			return "DOWN";
		case PSP_CTRL_LEFT:
			return "LEFT";
		case PSP_CTRL_LTRIGGER:
			return "LTRIGGER";
		case PSP_CTRL_RTRIGGER:
			return "RTRIGGER";
		// XBox layout
		case PSP_CTRL_TRIANGLE:
			return "BTNY";
		case PSP_CTRL_CIRCLE:
			return "BTNB";
		case PSP_CTRL_CROSS:
			return "BTNA";
		case PSP_CTRL_SQUARE:
			return "BTNX";
		default:
			return "UNKNOWN";
	}
}

bool remoteInit(char* host, unsigned short port) {

	sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON);
	sceUtilityLoadNetModule(PSP_NET_MODULE_INET);
	sceUtilityLoadNetModule(PSP_NET_MODULE_PARSEURI);
	sceUtilityLoadNetModule(PSP_NET_MODULE_PARSEHTTP);
	sceUtilityLoadNetModule(PSP_NET_MODULE_HTTP);

	if (sceHttpInit(20000) < 0) {
		pspDebugScreenPrintf("Could not init http library!\n");
	}

	int template = sceHttpCreateTemplate("Remote Control (PSP/v0.2)", 1, 0);
	if (template < 0) {
		pspDebugScreenPrintf("remoteInit: could not create template: returned %d\n", template);
		return false;
	}

	connectionID = sceHttpCreateConnection(template, host, "http", port, 0);
	if (connectionID < 0) {
		pspDebugScreenPrintf("remoteInit: could not create connection: returned %d\n", connectionID);
		return false;
	}

	return true;
}

bool remoteSetState(enum PspCtrlButtons bt, bool isDown) {

	int req = sceHttpCreateRequest(connectionID, PSP_HTTP_METHOD_POST, "/", 0);
	if (req < 0) {
		pspDebugScreenPrintf("Could not create request!\n");
		return false;
	}

	if (sceHttpSendRequest(req, NULL, 0) < 0) {
		pspDebugScreenPrintf("Could not send request!");
		return false;
	}

	sceHttpDeleteRequest(req);

	return true;
}
