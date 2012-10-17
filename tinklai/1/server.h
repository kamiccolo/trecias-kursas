#ifndef __SERVER_H
#define __SERVER_H
typedef struct TUser
{
	int userId;
	char userName[MAX_USERNAME_SIZE];
	TMQueue* inMQueue;
} TUser;

/*struct
{
	TUser* users;
} */
typedef TMQueue TMainBuffer;

void processNewFork(SOCKET socketFD, struct sockaddr_in* addr_cli, TMainBuffer* mainBuffer);

#endif
