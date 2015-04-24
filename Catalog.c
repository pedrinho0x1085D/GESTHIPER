#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Catalog.h"
#include "EstruturasAux.h"
#include "CusTypes.h"


/* MACROS *************************************************************/
#define ALFABETO 27

/*ESTRUTURAS DE DADOS**************************************************/
struct Catalog_ {
    /*array de árvores (ponteiros) para cada letra*/
    TreeCat indice[ALFABETO];

    int numcodigos[ALFABETO];
};
struct TreeCatNode{
	Codigo codigo;
	struct TreeCatNode *left, *right;
};
/*************************/

/*IMPLEMENTAÇÃO *******************************************************/
TreeCat newNode(Codigo c){
TreeCat new=malloc(sizeof(struct TreeCatNode));
new->codigo=strdup(c);
new->left=new->right=NULL;
return new;
}
Catalog newCat() {
    int i;
    Catalog novoindice;

    /*Aloca memória para o indice*/
    novoindice = (Catalog) malloc(sizeof (struct Catalog_));
    if (novoindice == NULL)
        return NULL;
    /*Inicializa indice*/
    for (i = 0; i < ALFABETO; i++) {
        novoindice->indice[i] = NULL;
	novoindice->numcodigos[i]=0;
    
}

   

    return novoindice;
}

void Cat_dispose(Catalog index) {
    int i;

    /*Verificar se o index está vazio*/
    if (index != NULL) {
        /*Libertar memória*/
        for (i = 0; i < ALFABETO; i++) {
            if (index->indice[i] != NULL)
                disposeTreeCatC(index->indice[i]);
        }
	free(index);

    }
    /*Libertar a memória ocupada pelo indice*/
    free(index);

}
void disposeTreeCatC(TreeCat t){
if(t){
disposeTreeCatC(t->left);
disposeTreeCatC(t->right);
free(t);
}
}
static int hashFuncCat(Codigo codigo) {
    char firstletter;

    firstletter = toupper(codigo[0]) - 'A' + 1;
    if ((firstletter < 0) || (firstletter > 26))
        firstletter = 0;

    return (int) firstletter;
}
TreeCat TreeCat_insert(TreeCat t,Codigo c){
TreeCat aux=t;
if(!aux) return newNode(c);
else if(strcmp(t->codigo,c)>0) t->left=TreeCat_insert(t->left,c);
else if(strcmp(t->codigo,c)<0) t->right=TreeCat_insert(t->right,c);
return aux;

}
Catalog Cat_insert(Catalog index, Codigo codigo) {
    int posicao;
    Catalog ca = index;
    posicao = hashFuncCat(codigo);
    ca->indice[posicao]=TreeCat_insert(ca->indice[posicao],codigo);
    ca->numcodigos[posicao]++;
    return ca;
}



int Cat_getNumCodigos(Catalog index,Codigo c) {
    int pos=hashFuncCat(c);

    return index->numcodigos[pos];
}



Boolean TreeCat_search(TreeCat t, Codigo c){
TreeCat aux=t;
Boolean found=FALSE;
while(aux&&!found){
if(strcmp(aux->codigo,c)>0) aux=aux->left;
else if(strcmp(aux->codigo,c)<0) aux=aux->right;
else found=TRUE;
}
return found;
}
Boolean Cat_searchCode(Catalog c, Codigo codigo) {
    int pos = hashFuncCat(codigo);
    return TreeCat_search(c->indice[pos], codigo);
}

CodigoArray CAT_getCodigos(TreeCat t, CodigoArray c){
	CodigoArray aux=c;
	if(t){
	aux=CAT_getCodigos(t->left,aux);
	aux=CA_insert(aux,t->codigo);
	aux=CAT_getCodigos(t->right,aux);
}
	return aux;
}

CodigoArray TreeCatCatoString_t(TreeCat t){
CodigoArray aux=newCA();
aux=CAT_getCodigos(t,aux);
return aux;
}

CodigoArray Cat_getTreeToArray(Catalog c, Codigo codigo) {
    int pos = hashFuncCat(codigo);
    return TreeCatCatoString_t(c->indice[pos]);
}

