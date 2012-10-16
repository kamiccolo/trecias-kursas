#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "defaults.h"
#include "server.h"
#include "mQueue.h"

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
	serv_addr.sin_port = (htons(portNo));
	serv_addr.sin_addr.s_addr = INADDR_ANY; /* ip adress of machine server is running. Now obtained automatically. */
	
	if(bind(sockFD, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("Error binding the socket!\n");
		close(sockFD);
		exit(1);
	}
	
	listen(sockFD, MAX_WAITING_CONS);
	
	while(true)
	{
		newSockFD = accept(sockFD, (struct sockaddr*) &cli_addr, (socklen_t*) &cliLen);
		if(newSockFD < 0)
		{
			printf("Error on accepting socket!\n");
		}
		
		int pid = fork();
		if(pid < 0)
		{
			printf("Error on fork!\n");
		}
		else
		{
			if(pid == 0)
			{
				/* processNewFork(); */
				exit(0);
			}
		}
		close(newSockFD);
	}
	return 0;
}
