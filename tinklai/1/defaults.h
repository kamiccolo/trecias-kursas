#ifndef __DEFAULTS_H
#define __DEFAULTS_H

#define MAX_BUFFER_SIZE 256
#define HEADER_SIZE 4
#define DEFAULT_PORT 11111
#define MAX_WAITING_CONS 5
#define MAX_USERNAME_SIZE 20
#define PACKET_SIZE 256
#define DEFAULT_IP 212.122.89.221

typedef enum
{
	JOIN_COMMAND = 1,
	SEND_COMMAND = 2,
	GETL_COMMAND = 3,
	GETM_COMMAND = 4,
	EXIT_COMMAND = 9,
	
	LOGB_COMMAND = 11,
	LIST_COMMAND = 12,
	MESS_COMMAND = 13,
	
	UNKNOWN_COMMAND = 0x19
	
} TCommand;

void intcpy(char* marshaledPacket, TCommand newCommand, int position);

typedef int SOCKET;

int unmarshalPacket(char* packetToUnmarshal, char* unmarshaledData);
void marshalPacket(char* dataToMarshal, char* marshaledPacket);

int sendData(SOCKET sockFD, char* dataToSend);
int getData(SOCKET sockFD, char* buffer);
#endif
