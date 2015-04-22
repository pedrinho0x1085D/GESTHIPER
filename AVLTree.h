/*
 *        __      __   ______
 *       / /     / /  |____  \
 *      / /     / /     ___| |
 *     / /     / /     |___  |
 *    / /___  / /      ____| |
 *   /_____/ /_/      |______/
 *
 *
 *  Ficheiro: AVLTree.h
 *
 */

#ifndef _ARVORESAVL_H_
#define _ARVORESAVL_H_
#include "EstruturasAux.h"
#include "Compras.h"
/*ESTRUTURAS DE DADOS PÃšBLICAS*****************************************/
typedef struct NodoArvoreAVL_ *NodoArvoreAVL;
typedef struct ArvoreAVL_ *ArvoreAVL;


/*MACROS **************************************************************/
#define NO_PESO_ESQUERDA	1
#define NO_BALANCEADO		0
#define NO_PESO_DIREITA 	-1

/*FUNÃ‡Ã•ES PÃšBLICAS*****************************************************/
/**
 * Criação de uma Árvore AVL 
 * @param compara Função de comparação 
 * @param destroi Função que permitirá o apagamento da árvore
 * @return Nova árvore
 */
ArvoreAVL cria_ArvoreAVL(int (*compara) (const void *valor1, const void *valor2), void (*destroi) (void *valor));
void destroi_ArvoreAVL_aux(ArvoreAVL arvore, NodoArvoreAVL nodo);
int insere_ArvoreAVL_aux(ArvoreAVL arvore, NodoArvoreAVL *nodo, const void *valor, int *balanceada);
/**
 * Função de destruição da Árvore
 * @param arvore Árvore a ser destruída
 */
void destroi_ArvoreAVL(ArvoreAVL arvore);
/**
 * Função de inserção na Árvore AVL
 * @param arvore Árvore que receberá o valor
 * @param valor Valor a ser inserido na árvore
 * 
 */
int insere_ArvoreAVL(ArvoreAVL arvore, const void *valor);
/**
 * Função de pesquisa de um valor na Árvore AVL
 * @param arvore Árvore a ser percorrida
 * @param valor Valor a ser procurado
 * @return 1 se o valor existir na árvore, 0 caso contrário
 */
int pesquisa_ArvoreAVL(ArvoreAVL arvore, void *valor);
int pesquisa_NodoArvoreAVL(struct NodoArvoreAVL_* arvore, void* valor, int (*compara) (const void *valor1, const void *valor2));
/**
 * Retorna o tamanho (Nr de Elementos) da árvore
 * @param arvore Árvore a ser consultada
 * @return Tamanho da árvore ou -1 se se tratar de um apontador para NULL
 */
int gettamanho_ArvoreAVL(ArvoreAVL arvore);
/**
 * Retorna um objecto do Tipo CodigoArray com os valores ordenados
 * @param tree Árvore a ser percorrida
 * @return CodigoArray com os valores linearizados da árvore
 */
CodigoArray TreeToString(ArvoreAVL tree);
CodigoArray treeTraversal_aux(struct NodoArvoreAVL_* avl, CodigoArray ca);
/**
 * Retorna o valor da árvore tal 
 * @param tree Árvore a ser percorrida
 * @param valor valor(Por exemplo um código) a ser procurado
 * @return Objecto tal que a função de comparação seja 0, ou NULL caso não exista
 */
Cliente getCli(ArvoreAVL tree, Codigo codigo);

Produto getProd(ArvoreAVL tree, Codigo codigo);
/**
 * Retorna a raíz de uma Árvore
 * @param tree Árvore a ser consultada
 * @return Raíz de uma Árvore
 */
NodoArvoreAVL getTree(ArvoreAVL tree);
NodoArvoreAVL novonodo_ArvoreAVL(const void *valor);
void rodaresquerda_ArvoreAVL(NodoArvoreAVL *nodo_a_rodar);
void rodardireita_ArvoreAVL(NodoArvoreAVL *nodo_a_rodar);

/*
 Funções auxiliares À resolução das queries
 */
Table constroiTabela(ArvoreAVL arvore,Table t);
Table constroiTabela_aux(NodoArvoreAVL nodo, Table tab);
Par procuraClientesSemCompras(ArvoreAVL arvore,Par p);
Par procuraClientesSemCompras_aux(NodoArvoreAVL avl, Par p);
Par procuraProdutosNaoComprados(ArvoreAVL arvore,Par p);
Par procuraProdutosNaoComprados_aux(NodoArvoreAVL avl, Par p);

CodigoArray compraTodos(ArvoreAVL avl,CodigoArray ca);
CodigoArray compraTodos_aux(NodoArvoreAVL avl, CodigoArray ca);
ArvoreQtd constroiArvore(ArvoreAVL avl,ArvoreQtd aq);
ArvoreQtd constroiArvore_aux(NodoArvoreAVL nodo, ArvoreQtd aq);
TabelaCSV carregaClientesCSV_AUX(ArvoreAVL avl, TabelaCSV csv);
TabelaCSV carregaClientes_aux(NodoArvoreAVL avl, TabelaCSV csv);
ArvoreQtd constroiArvoreQtd (ArvoreAVL avl);
ArvoreQtd constroiArvoreQtd_aux(NodoArvoreAVL nodo, ArvoreQtd aq);
#endif
