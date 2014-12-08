#include <stdlib.h>
#include "MyString.h"
#include <stdio.h>
#include <string.h>

int main(){
	char * p = "ChaChanger";
	char * t = "Hello ChaChanger How are you! Ok ";
	int * n = buildNext(p);
	int i ;
	for(i = 0; i<strlen(p);i++)
		printf(" %d ",n[i]);
	printf("\n");
	printf("ÂùÁ¦Æ¥Åä %d \n",matchString(p,t));
	//printf("%d \n",matchString2(p,t));
	printf("KMPÆ¥Åä %d \n",kmpMatch(p,t));
	return 0;
}