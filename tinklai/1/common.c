#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "defaults.h"

void intcpy(char* marshaledPacket, TCommand newCommand, int position)
{
	int i = (int) newCommand;
	memcpy(marshaledPacket+position, &i, 4);
}

void  marshalPacket(char* dataToMarshal, char* marshaledPacket)
{
	
	char sendCommand[5] = "SEND ";
        char joinCommand[5] = "JOIN ";
        char listCommand[4] = "LIST";
        char getCommand[5] = "GETM ";
        char exitCommand[4] = "EXIT";

	
	char header[3] = "MZ\0";

	strcpy(marshaledPacket, (char*)header);
	if(!strncmp(dataToMarshal, (char*) &exitCommand, 4))
	{
		intcpy(marshaledPacket, EXIT_COMMAND, HEADER_SIZE);
	}
	else
	{
		if(!strncmp(dataToMarshal, (char*) sendCommand, 5))
		{
			intcpy(marshaledPacket, SEND_COMMAND, HEADER_SIZE);
		}
		else
		{
			intcpy(marshaledPacket, UNKNOWN_COMMAND, HEADER_SIZE);
		}

        	strcpy(marshaledPacket+9, dataToMarshal+5);
	}
	marshaledPacket[2]='1';
	marshaledPacket[3]='1';
	
	printf("Data to marshal (%i): %s", strlen(dataToMarshal), dataToMarshal);
	printf("\nMarshaled packet (%i): %s", strlen(marshaledPacket),  marshaledPacket);

}

int unmarshalPacket(char* packetToUnmarshal, char* unmarshaledData)
{
	char header[3] = "MZ\0";
	if(!strncmp(packetToUnmarshal, header, 2))
	{
		memcpy(unmarshaledData, packetToUnmarshal+2, 4);
		strcpy(unmarshaledData+4, packetToUnmarshal+HEADER_SIZE+4);
		return 0;
	}
	return 1;
}

int sendData(SOCKET sockFD, char* dataToSend)
{
        char packetToSend[PACKET_SIZE] = {0};
        int bytesLeft = PACKET_SIZE;
        int bytesSent = 0;

        marshalPacket(dataToSend, (char*) &packetToSend);
        while(bytesLeft>0)
        {
                bytesSent = write(sockFD, (char*)  packetToSend+PACKET_SIZE-bytesLeft, bytesLeft);

                if(bytesSent < 0)
                {
                        printf("Error sending the packet at byte: %i\n", PACKET_SIZE-bytesLeft);
			return 0;
                }
                else
                {
                        bytesLeft-=bytesSent;
                }

        }
return PACKET_SIZE-bytesLeft;
}

