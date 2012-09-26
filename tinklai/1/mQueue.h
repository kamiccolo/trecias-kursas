#ifndef __MQUEUE_H
#define __MQUEUE_H

#define MESSAGE_MAX_SIZE	512
#define MESSAGE_MAX_COUNT	10

typedef enum 
{
	false = 0,
	true = 1
} bool;

typedef struct TMString
{
	char text[MESSAGE_MAX_SIZE];
} TMString;

typedef struct TMessage
{
	TMString mString;
	struct TMessage* nMessage;	
} TMessage;

typedef struct
{
	int count;
	struct TMessage* fMessage;
	struct TMessage* lMessage;
} TMQueue;

TMQueue* mqInit();
TMessage* mInit(char* mBody);

void mqDestroy(TMQueue* qToDestroy);
void mDestroy(TMessage* mToDestroy);

bool mPush(char* mBody, TMQueue* mqToUse);
char* mPop(TMQueue* mqToUse);
char* mGet(TMQueue* mqToUse);
#endif
