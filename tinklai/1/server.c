#include <stdio.h>
#include <stdlib.h>	
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "defaults.h"
#include "mQueue.h"
#include "server.h"

int main()
{
	SOCKET sockFD, newSockFD;
	int portNo, cliLen;
	struct sockaddr_in serv_addr, cli_addr;
	
	sockFD = socket(AF_INET, SOCK_STREAM, 0);
	if(sockFD < 0)
	{
		printf("Error opening a socket!\n");
		exit(1);
	}
	
	portNo = DEFAULT_PORT;

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portNo);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); /* ip adress of machine server is running. Now obtained automatically. */
	printf("INADDR_ANY: %d\n", INADDR_ANY);
	
	if(bind(sockFD, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("Error binding the socket!\n");
		close(sockFD);
		exit(1);
	}
	
	listen(sockFD, MAX_WAITING_CONS);
	TMQueue* mainBuffer = mqInit();
	
	while(true)
	{
		newSockFD = accept(sockFD, (struct sockaddr*) &cli_addr, (socklen_t*) &cliLen);
		if(newSockFD < 0)
		{
			printf("Error on accepting socket!\n");
		}
		else
		{
			char connectedIP[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &cli_addr.sin_addr, connectedIP, INET_ADDRSTRLEN);
			printf("New connection accepted: %s\n", connectedIP);
	
			int pid = fork();
			if(pid < 0)
			{
				printf("Error on fork!\n");
			}
			else
			{
				if(pid == 0)
				{	
				/* need to create and pass logged in users structure for this function and buffers */
					processNewFork(newSockFD, (struct sockaddr_in*) &cli_addr, (TMainBuffer*) mainBuffer);
					exit(0);
				}	
			}	
		}
		
	}
	printf("Closing main socket...\n");
	close(newSockFD);
	return 0;
}

void processNewFork(SOCKET sockFD, struct sockaddr_in* addr_cli, TMainBuffer* mainBuffer)
{
	char sendCommand[5] = "SEND ";
	char joinCommand[5] = "JOIN ";
	char listCommand[4] = "LIST";
	char getCommand[5] = "GETM ";
	char exitCommand[4] = "EXIT";


	/* write(sockFD,"Test!\n", 6);  *//*for fast telnet testing temporary */
	char sBuffer[PACKET_SIZE+1] = {0};
	char dBuffer[PACKET_SIZE-HEADER_SIZE+2] = {0};
	int newCommand = 0;
	int got = 0;

	while(true)
	{
		/* pataisyti i buferizuota rydinga */
		got = read(sockFD, sBuffer, PACKET_SIZE);
		if(got>0)
		{
			got = unmarshalPacket(sBuffer, dBuffer);
			memcpy(&newCommand, dBuffer, 4);
			printf("Got (%i): %s\n", strlen(sBuffer+sizeof(TCommand)));
			printf("Unmarshaled message(%i): %s\n", strlen(dBuffer+sizeof(TCommand)), dBuffer+sizeof(TCommand));
			printf("Unmarshaled command: %i\n", newCommand);

			if(newCommand == EXIT_COMMAND)
			{	
				printf("Closing child socket...\n");
				close(sockFD);
			}
			/*
			exit(1);
			*/
		}
	}
}
