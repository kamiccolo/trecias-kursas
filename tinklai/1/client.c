#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "mQueue.h"
#include "defaults.h"
#include "client.h"

int main(int argc, char* argv[])
{
	int usedPort = DEFAULT_PORT;
	struct sockaddr_in serv_addr;
	struct hostent* server;
	char serverIP[INET_ADDRSTRLEN];

	char localBuffer[MAX_BUFFER_SIZE+1] = {0};

	if(argc<2)
	{
		printf("Pleae use './client ip [port]' instead!\n");
		exit(1);
	}
	if(argc==3)
	{
		usedPort = atoi(argv[1]);
	}
	
	SOCKET sockFD = socket(AF_INET, SOCK_STREAM, 0);
	if(sockFD<0)
	{
		printf("Error opening the socket!");
		exit(1);
	}
	
	server = gethostbyname(argv[1]);

	if(server == NULL)
	{
		printf("Error, no such a host!\n");
		close(sockFD);
		exit(1);
	}	

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(usedPort);
	inet_pton(AF_INET, argv[1], (struct in_adrr*) &(serv_addr.sin_addr));
	if(connect(sockFD, (struct sockaddr*) &(serv_addr), sizeof(serv_addr))<0)
	{
		printf("Error connecting to server!\n");
		exit(1);
	}
	
	while(true)
	{
		char ciBuffer[PACKET_SIZE-HEADER_SIZE] = {0};
		int state = 0;


		printf("Please, enter a command:\n");
		/* scanf("%252[0-9a-Z ]s", (char*) &ciBuffer); */
		fgets(ciBuffer, sizeof(ciBuffer)-2, stdin);

		printf("\nEntered (%i): %s\n", strlen(ciBuffer),  (char*) &ciBuffer);

		if(handleInput(sockFD, (char*) &ciBuffer, &state))
		{
			printf("Error entering a command!\n");
		}
	}
	
	return 0;
}

int handleInput(SOCKET sockFD, char* ciBuffer, int* state)
{
	printf("Input is(%i): %s\n", strlen(ciBuffer), ciBuffer);
/*
	char sendCommand[5] = "SEND ";
	char joinCommand[5] = "JOIN ";
	char listCommand[4] = "LIST";
	char getCommand[5] = "GETM ";
	char exitCommand[4] = "EXIT";
*/
	printf("cmp (%i): %i", sizeof(EXIT_COMMAND), EXIT_COMMAND);
	/* char* command = strndup(ciBuffer, 4); */
	if((*state) == 0)
	{
		if(strlen(ciBuffer)>3)	
		{
			/* write(sockFD, ciBuffer, 273); */
			if(sendData(sockFD, ciBuffer))
			{
				(*state) = 1;
			}
			/*send */
		}
		else
		{
			printf("Bad input!\n");
	
		}
	}
	else
	{
		/* receive */
	}
	return 0;
}
