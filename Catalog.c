#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Catalog.h"
#include "AVLTree.h"
#include "EstruturasAux.h"
#include "CusTypes.h"


/* MACROS *************************************************************/
#define ALFABETO 27

/*ESTRUTURAS DE DADOS**************************************************/
struct Catalog_ {
    /*array de árvores (ponteiros) para cada letra*/
    ArvoreAVL indice[ALFABETO];

    int numcodigos;
};

/*************************/
int compara(const void* valor1, const void* valor2) {
    return strcmp((Codigo) valor1, (Codigo) valor2);
}

void destroi(void* valor1) {
    free(valor1);
}

/*IMPLEMENTAÇÃO *******************************************************/
Catalog newCat() {
    int i;
    Catalog novoindice;

    /*Aloca memória para o indice*/
    novoindice = (Catalog) malloc(sizeof (struct Catalog_));
    if (novoindice == NULL)
        return NULL;
    /*Inicializa indice*/
    for (i = 0; i < ALFABETO; i++) {
        novoindice->indice[i] = cria_ArvoreAVL(&compara, &destroi);
    }

    novoindice->numcodigos = 0;

    return novoindice;
};

void Cat_dispose(Catalog index) {
    int i;

    /*Verificar se o index está vazio*/
    if(index!=NULL){
    /*Libertar memória*/
    for (i = 0; i < ALFABETO; i++) {
        if (index->indice[i] != NULL)
            destroi_ArvoreAVL(index->indice[i]);
    }

    }
    /*Libertar a memória ocupada pelo indice*/
    free(index);
    
}

static int hashFuncCat(Codigo codigo) {
    char firstletter;

    firstletter = toupper(codigo[0]) - 'A' + 1;
    if ((firstletter < 0) || (firstletter > 26))
        firstletter = 0;

    return (int) firstletter;
}

Catalog Cat_insert(Catalog index, Codigo codigo) {
    int posicao;
    Catalog ca=index;
    posicao = hashFuncCat(codigo);
    /*Sé já existe termina*/
    if (insere_ArvoreAVL(ca->indice[posicao], codigo) == 1)
        return index;
    else
        ca->numcodigos++;


    return ca;
};

int Cat_getNumCodigos(Catalog index) {
    int posicao, total = 0;

    for (posicao = 0; posicao < ALFABETO; posicao++) {
        if (index->indice[posicao] != NULL)
            total += gettamanho_ArvoreAVL(index->indice[posicao]);
    };

    return total;
};

ArvoreAVL Cat_getTree(Catalog index, Codigo primeira_letra) {
    int posicao;

    posicao = hashFuncCat(primeira_letra);

    return index->indice[posicao];
}

Boolean Cat_searchCode(Catalog c, Codigo codigo) {
    int pos = hashFuncCat(codigo);
    return pesquisa_ArvoreAVL(c->indice[pos], codigo);
}

CodigoArray Cat_getTreeToArray(Catalog c, Codigo codigo) {
    int pos = hashFuncCat(codigo);
    return TreeToString(c->indice[pos]);
} 