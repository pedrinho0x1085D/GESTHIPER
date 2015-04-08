#include <stdlib.h>
#include <string.h>
#include "Codigo.h"
#include "Catalog.h"


/*Implementação*/
CodigoArray new(){
    return NULL;
    }
int getSize(CodigoArray ca){
    int i=0;
    while(ca[i]!=NULL)
        i++;
    return i;
}
void insert(CodigoArray ca, Codigo co){
    ca[getSize(ca)]=malloc(strlen(co)+1);
    ca[getSize(ca)]=strdup(co);
}

void dispose(CodigoArray ca){
    int i=0;
    while(i<getSize(ca))
        free(ca[i]);
    free(ca);
}

int in(Codigo co, CodigoArray ca){
    int flag=0,i;
    for(i=0;i<getSize(ca)&&(!flag);i++)
        if(strcmp(co,ca[i]))flag=1;
    return flag;
}

CodigoArray getFirstN(CodigoArray ca, int n){
    int i;
    int min=min(n,getSize(ca));
    CodigoArray caux=new();
    for(i=0;i<min;i++){
        insert(caux,ca[i]);
    }
    return caux;
}
int min(int x1,int x2){
    if(x1>x2) return x2;
    if(x2>x1) return x1;
    if(x1==x2) return x1;
}

Codigo get(CodigoArray ca, int i){
    return strdup(ca[i]);
}