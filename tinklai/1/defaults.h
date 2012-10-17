#ifndef __DEFAULTS_H
#define __DEFAULTS_H

#define MAX_BUFFER_SIZE 256
#define DEFAULT_PORT 11111
#define MAX_WAITING_CONS 5
#define MAX_USERNAME_SIZE 20
#define PACKET_SIZE 256
#define DEFAULT_IP 212.122.89.221

typedef int SOCKET;

int unmarshalPacket(char* packet);
void marshalPacket(char* dataToMarshal, char* marshaledPacket);

int sendData(SOCKET sockFD, char* dataToSend);
int getData(SOCKET sockFD, char* buffer);
#endif
