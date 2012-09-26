#include <stdlib.h>
#include <string.h>

#include "mQueue.h"

TMQueue* mqInit()
{
        TMQueue* retTmp = (TMQueue*) malloc(sizeof(TMQueue));

        retTmp -> count = 0;
        retTmp -> lMessage = NULL;
        retTmp -> fMessage = NULL;

        return retTmp;
}

TMessage* mInit(char* mBody)
{
        TMessage* retTmp = malloc(sizeof(TMessage));
        retTmp -> nMessage = NULL;
        strcpy(mBody, (char*) &(retTmp -> mString.text));
        return retTmp;
}

void mDestroy(TMessage* mToDestroy)
{
	if(mToDestroy != NULL)
	{
		mDestroy(mToDestroy -> nMessage);
		free(mToDestroy);
	}
}

void mqDestroy(TMQueue* qToDestroy)
{
	if(qToDestroy != NULL)
	{
		mDestroy(qToDestroy -> fMessage);
		free(qToDestroy);
	}
}

bool mPush(char* mBody, TMQueue* mqToUse)
{
	if(mqToUse -> count < MESSAGE_MAX_COUNT)
	{
		TMessage* messageToPush = malloc(sizeof(TMessage));
		messageToPush -> nMessage = NULL;
		
		if(!mqToUse -> count)
		{
			mqToUse -> fMessage = messageToPush;
		}
		else
		{
			mqToUse -> lMessage -> nMessage = messageToPush;
		}
		
		mqToUse -> lMessage = messageToPush;
		mqToUse -> count++;

		strcpy((char*)&(messageToPush -> mString.text), mBody);
		return true;
	}
	else
	{
		return false;
	}
}

char* mPop(TMQueue* mqToUse)
{
	if(mqToUse == NULL)
	{
		return NULL;
	}
	else
	{
		char* retTmp = malloc(strlen((char*) &(mqToUse -> fMessage -> mString.text)));
		strcpy(retTmp, (char*) &(mqToUse -> fMessage -> mString.text));

		TMessage* secondMessage = mqToUse -> fMessage -> nMessage;
		free(mqToUse -> fMessage);
		mqToUse -> fMessage = secondMessage;
		mqToUse -> count--;	
		return retTmp;
	}
}

char* mGet(TMQueue* mqToUse)
{
	if(mqToUse == NULL)
	{
		return NULL;
	}
	else
	{
		return (char*) &(mqToUse -> fMessage -> mString.text);
	}
}
