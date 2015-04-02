/*
*        __      __   ______
*       / /     / /  |____  \
*      / /     / /     ___| |
*     / /     / /     |___  |
*    / /___  / /      ____| |
*   /_____/ /_/      |______/
*
*
*  Ficheiro: arvoresAVL.h
*
*/

#ifndef _ARVORESAVL_H_
#define _ARVORESAVL_H_

/*ESTRUTURAS DE DADOS PÃšBLICAS*****************************************/
typedef struct NodoArvoreAVL_ *NodoArvoreAVL;
typedef struct ArvoreAVL_ *ArvoreAVL;


/*MACROS **************************************************************/
#define NO_PESO_ESQUERDA	1
#define NO_BALANCEADO		0
#define NO_PESO_DIREITA 	-1

/*FUNÃ‡Ã•ES PÃšBLICAS*****************************************************/
ArvoreAVL cria_ArvoreAVL(int (*compara) (const void *valor1, const void *valor2), void (*destroi) (void *valor));
void destroi_ArvoreAVL(ArvoreAVL arvore);
int insere_ArvoreAVL(ArvoreAVL arvore,const void *valor);
int pesquisa_ArvoreAVL(ArvoreAVL arvore, void **valor);
int gettamanho_ArvoreAVL(ArvoreAVL arvore);
int getnuminsercoes_ArvoreAVL(ArvoreAVL arvore,void *valor);
CodigoArray TreeToString(ArvoreAVL tree);
void* get(ArvoreAVL tree, void* valor);
NodoArvoreAVL getTree(ArvoreAVL tree);
void nuncaComprados(ArvoreAVL tree,CodigoArray ca);
void constroiTabela(ArvoreAVL arvore, Table table);
#endif
