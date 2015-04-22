#include <string.h>
#include <stdlib.h>
#include "CusTypes.h"

char *strdup(const char *str)
{
    char *b;
    b=malloc(strlen(str)+1);
    if(!b) return NULL;
    strcpy(b, str);
    return b;
}

int min(int x1, int x2){
	if(x1<=x2) return x1;
	else return x2;
}