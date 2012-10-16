#include <stdio.h>
#include <string.h>

#include <stdlib.h>

#include "mQueue.h"

int main()
{
	TMQueue* mainQ = mqInit();
	char mainM[] = "aaa";
	char bM[] = "bbbb";
	char cM[] = "ccccccc";
	printf("%s, %s, %s \n\n", (char*) mainM, (char*) bM, (char*) cM);
	
	printf("Push test: \n");
	mPush((char*) &mainM, mainQ);
	mPush((char*) &bM, mainQ);
	printf("First value: %s,\nPushed value: %s,\nCount: %i\n",(char*) &(mainQ -> fMessage -> mString.text), (char*) &(mainQ -> lMessage -> mString.text), mainQ -> count);
	printf("Last value: %s\n\n", (char*) &(mainQ -> lMessage -> mString.text));
	

	
	printf("Pop test:\n");
	char* newPoo = (char*) mPop(mainQ);
	printf("Poo value: %s\n", newPoo); 

	printf("First value: %s\n", (char*) &(mainQ -> fMessage -> mString.text));
	printf("count: %i\n", mainQ -> count);
	printf("Last value: %s\n\n", (char*) &(mainQ -> lMessage -> mString.text));
	free(newPoo);


	printf("mGet test: \n");
	char* newGet = (char*) mGet(mainQ);
	printf("getValue: %s\n", newGet);
	printf("First value: %s\n", (char*) &(mainQ -> fMessage -> mString.text));
	printf("count: %i\n\n", mainQ -> count);
	
	printf("mDestroy test:\n");
	mDestroy(mainQ -> fMessage);
	mainQ -> count = 0;
	mPush((char*)cM, mainQ);
	printf("count: %i\n\n", mainQ -> count);	
	mqDestroy(mainQ);

	return 0;
}
