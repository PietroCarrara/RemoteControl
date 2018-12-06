#include "remote.h"

static int sockID = -1;

#define HTONS(n) (((((unsigned short)(n) & 0xFF)) << 8) | (((unsigned short)(n) & 0xFF00) >> 8))

// Well... I couldn't think of any better way of doing this ;)
static const char* buttonToString(enum PspCtrlButtons bt) {
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

bool remoteInit(in_addr_t host, uint16_t port) {

	pspDebugScreenPrintf("Creating socket...\n");

	sockID = sceNetInetSocket(AF_INET, SOCK_STREAM, 0);
	if (sockID < 0) {
		printf("Couldn't create socket!\n");
	}

	struct sockaddr_in addr;

    addr.sin_family = AF_INET; 
    addr.sin_port = HTONS(port); 
    addr.sin_addr.s_addr = host; 

	pspDebugScreenPrintf("Connecting to: %X:%d\n", addr.sin_addr.s_addr, HTONS(addr.sin_port));

	pspDebugScreenPrintf("Set blocking mode...\n");

	// Set noblock to false
	int NoBlock = 0;
    sceNetInetSetsockopt(sockID, SOL_SOCKET, SO_NONBLOCK, &NoBlock, sizeof(NoBlock)); 

	pspDebugScreenPrintf("Connecting...\n");

    int err = sceNetInetConnect(sockID, (struct sockaddr *)(&addr), sizeof(addr)); 
	if (err < 0) {
		pspDebugScreenPrintf("Could not connect to the host: returned %d\n", err);
		return false;
	}

	return true;
}

bool remoteSetState(enum PspCtrlButtons bt, bool isDown) {

	char url[128];

	sprintf(url, "/SetState/%s/%s", buttonToString(bt), isDown ? "true" : "false");

	printf("%s\n", url);

	return true;
}

// unsigned char == byte
bool remoteSetValue(char* stick, unsigned char val) {
	
	char url[128];

	sprintf(url, "/SetValue/%s/%d", stick, val);

	printf("%s\n", url);

	return true;
}
