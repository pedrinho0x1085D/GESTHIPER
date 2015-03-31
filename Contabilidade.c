#include <stdlib.h>
#include "AVLTree.h"
#include "Contabilidade.h"

struct contnode_{
    char* codigo;
    int vendasN[12],vendasP[12];
    int faturaN[12],faturaP[12];
    
};
struct conTree_{
    ArvoreAVL arvore;
};

/*Copiei estas duas do catalog.c nao sei se é só isto*/
int comparaCompra(const Contab valor1,const Contab valor2){
	return strcmp((char*)valor1->codigo,(char*)valor2->codigo);
}

void destroi(void* valor1){
	free(valor1);
}

static Contab new(){
    Contab aux=malloc(sizeof(struct contnode_));
    int i;
    aux->codigo=NULL;
    for(i=0;i<12;i++){
        aux->faturaN[i]=0;
        aux->faturaP[i]=0;
        aux->vendasN[i]=0;
        aux->vendasP[i]=0;
    }
    return aux;
}

Contab new(char* codigo){
    Contab aux=malloc(sizeof(struct contnode_));
    int i;
    aux->codigo=strdup(codigo);
    for(i=0;i<12;i++){
        aux->faturaN[i]=0;
        aux->faturaP[i]=0;
        aux->vendasN[i]=0;
        aux->vendasP[i]=0;
    }
    return aux;
}

conTree new(){
    conTree aux=malloc(sizeof(struct conTree));
    aux->arvore=cria_ArvoreAVL(&comparaCompra,&destroi);
    return aux;
}