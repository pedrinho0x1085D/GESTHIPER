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
    ca[getSize(ca)]=malloc(10);
    ca[getSize(ca)]=strdup(co);
}

void dispose(CodigoArray ca){
    int i=0;
    while(i<getSize(ca))
        free(ca[i]);
    free(ca);
}
