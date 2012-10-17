#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "defaults.h"

void  marshalPacket(char* dataToMarshal, char* marshaledPacket)
{
        marshaledPacket[PACKET_SIZE] = 0;
        strcpy(dataToMarshal, marshaledPacket);

}

int sendData(SOCKET sockFD, char* dataToSend)
{
        char* packetToSend[PACKET_SIZE+1];
        int bytesLeft = PACKET_SIZE+1;
        int bytesSent = 0;

        marshalPacket(dataToSend, (char*) packetToSend);
        while(bytesLeft>0)
        {
                bytesSent = write(sockFD, (char*)  packetToSend[PACKET_SIZE+1-bytesLeft], bytesLeft);

                if(bytesSent < 0)
                {
                        printf("Error sending the packet at byte: %i\n", PACKET_SIZE+1-bytesLeft);
                }
                else
                {
                        bytesLeft-=bytesSent;
                }

        }
return PACKET_SIZE+1-bytesLeft;
}

