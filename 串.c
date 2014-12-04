#include <stdlib.h>
#include "MyString.h"
#include <stdio.h>

int main(){
	char * p = "Changer";
	char * t = "Hello Changer How are you! Ok Changer";
	printf("%d \n",matchString(p,t));
	printf("%d \n",matchString2(p,t));
	return 0;
}