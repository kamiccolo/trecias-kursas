#include <stdio.h>
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
		printf("Main interface:\n");
	}
	
	return 0;
}

