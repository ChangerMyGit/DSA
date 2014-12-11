#include <stdlib.h>
#include "MyString.h"
#include <stdio.h>
#include <string.h>

int mainString(){
	char * p1 = "chine chinchilla";
	char * p = "ABCDABD";
	char * t = "BBC ABCDAB ABCDABCDABDE";
	int * n = buildNext(p1);
	int i ;
	for(i = 0; i<strlen(p1);i++)
		printf(" %d ",n[i]);
	printf("\n");
	printf("ÂùÁ¦Æ¥Åä %d \n",matchString(p,t));
	//printf("%d \n",matchString2(p,t));
	printf("KMPÆ¥Åä %d \n",kmpMatch(p,t));
	return 0;
}