/*
 *        __      __   ______
 *       / /     / /  |____  \
 *      / /     / /     ___| |
 *     / /     / /     |___  |
 *    / /___  / /      ____| |
 *   /_____/ /_/      |______/
 * 
 * 
 *  Ficheiro: arvoresAVL.c
 *
 */

/* MÃ“DULOS NECESSÃ�RIOS ************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "AVLTree.h"
#include "EstruturasAux.h"
#include "Compras.h"
/* MACROS *************************************************************/
#define ESQUERDA 1
#define DIREITA 2

/*ESTRUTURAS DE DADOS**************************************************/
struct NodoArvoreAVL_ {
    void *valor;
    int factor;
    struct NodoArvoreAVL_ *esquerda;
    struct NodoArvoreAVL_ *direita;
    int numinsercoes;
};

struct ArvoreAVL_ {
    int tamanho;
    int (*compara) (const void *valor1, const void *valor2);
    void (*destroi) (void *valor);
    struct NodoArvoreAVL_ *raiz;
};


/*DECLARAÃ‡ÃƒO DAS FUNÃ‡Ã•ES PRIVADAS**************************************/

static void* get_aux(struct NodoArvoreAVL_* tree, int (*compara) (const void *valor1, const void *valor2), void* valor);
static CodigoArray treeTraversal_aux(struct NodoArvoreAVL_* avl, CodigoArray ca);
static void destroi_ArvoreAVL_aux(ArvoreAVL arvore, NodoArvoreAVL nodo);
static void destroi_ArvoreAVL_esquerda(ArvoreAVL arvore, NodoArvoreAVL nodo);
static void destroi_ArvoreAVL_direita(ArvoreAVL arvore, NodoArvoreAVL nodo);
static int insere_ArvoreAVL_aux(ArvoreAVL arvore, NodoArvoreAVL *nodo, const void *valor, int *balanceada);
static NodoArvoreAVL novonodo_ArvoreAVL(const void *valor);
static void rodaresquerda_ArvoreAVL(NodoArvoreAVL *nodo);
static void rodardireita_ArvoreAVL(NodoArvoreAVL *nodo);
static int pesquisa_NodoArvoreAVL(NodoArvoreAVL_* arvore, void* valor, int(*compara)(const void*, const void*));
static void constroiTabela(NodoArvoreAVL nodo, Table tab);

/*IMPLEMENTAÃ‡ÃƒO DAS FUNÃ‡Ã•ES PÃšBLICAS***********************************/
ArvoreAVL cria_ArvoreAVL(int (*compara) (const void *valor1, const void *valor2), void (*destroi) (void *valor)) {
    ArvoreAVL novaArvoreAVL;

    novaArvoreAVL = (ArvoreAVL) malloc(sizeof (struct ArvoreAVL_));
    if (novaArvoreAVL == NULL)
        return NULL;

    novaArvoreAVL->tamanho = 0;
    novaArvoreAVL->raiz = NULL;
    novaArvoreAVL->compara = compara;
    novaArvoreAVL->destroi = destroi;

    return novaArvoreAVL;
}

void destroi_ArvoreAVL(ArvoreAVL arvore) {
    if (arvore != NULL) {
        if (arvore->raiz != NULL) {
            destroi_ArvoreAVL_aux(arvore, arvore->raiz);
        }
        free(arvore);
    }
}

int insere_ArvoreAVL(ArvoreAVL arvore, const void *valor) {
    int balanceada = 0;

    if (arvore->raiz == NULL) {
        arvore->raiz = novonodo_ArvoreAVL(valor);
        arvore->tamanho++;
        return 0;
    }
    return insere_ArvoreAVL_aux(arvore, &arvore->raiz, valor, &balanceada);
}

int gettamanho_ArvoreAVL(ArvoreAVL arvore) {
    if (arvore == NULL)
        return -1;
    return arvore->tamanho;
}

int pesquisa_NodoArvoreAVL(struct NodoArvoreAVL_* arvore, void* valor, int (*compara) (const void *valor1, const void *valor2)) {
    if (arvore == NULL) return 0;
    if (compara(arvore->valor, valor) > 0) return pesquisa_NodoArvoreAVL(arvore->esquerda, valor, compara);
    if (compara(arvore->valor, valor) < 0) return pesquisa_NodoArvoreAVL(arvore->direita, valor, compara);
    if (compara(arvore->valor, valor) == 0) return 1;
}

int pesquisa_ArvoreAVL(ArvoreAVL arvore, void *valor) {
    return pesquisa_NodoArvoreAVL(arvore->raiz, valor, arvore->compara);

}

/*IMPLEMENTAÃ‡ÃƒO DAS FUNÃ‡Ã•ES PRIVADAS***********************************/
static void destroi_ArvoreAVL_aux(ArvoreAVL arvore, NodoArvoreAVL nodo) {
    if (nodo == NULL) return;
    if (nodo->esquerda != NULL) destroi_ArvoreAVL_aux(arvore, nodo->esquerda);
    if (nodo->direita != NULL) destroi_ArvoreAVL_aux(arvore, nodo->direita);

    if (arvore->destroi != NULL)
        arvore->destroi(nodo->valor);
    free(nodo);
    nodo = NULL;
    arvore->tamanho--;
}

static int insere_ArvoreAVL_aux(ArvoreAVL arvore, NodoArvoreAVL *nodo, const void *valor, int *balanceada) {
    int valcompara;

    valcompara = arvore->compara(valor, (*nodo)->valor);
    if (valcompara < 0) {
        if ((*nodo)->esquerda == NULL) {
            (*nodo)->esquerda = novonodo_ArvoreAVL(valor); /*insere esquerda*/
            arvore->tamanho++;
            *balanceada = 0;
        } else
            insere_ArvoreAVL_aux(arvore, &(*nodo)->esquerda, valor, balanceada);

        /*Balancear inserÃ§Ã£o Ã  esquerda*/
        if (!(*balanceada)) {
            switch ((*nodo)->factor) {
                case NO_PESO_ESQUERDA:
                    rodaresquerda_ArvoreAVL(nodo);
                    *balanceada = 1;
                    break;
                case NO_BALANCEADO:
                    (*nodo)->factor = NO_PESO_ESQUERDA;
                    break;
                case NO_PESO_DIREITA:
                    (*nodo)->factor = NO_BALANCEADO;
                    *balanceada = 1;
            }
        }
    } else if (valcompara > 0) {
        if ((*nodo)->direita == NULL) {
            (*nodo)->direita = novonodo_ArvoreAVL(valor); /*insere direita*/
            arvore->tamanho++;
            *balanceada = 0;
        } else
            insere_ArvoreAVL_aux(arvore, &(*nodo)->direita, valor, balanceada);

        /*Balancear inserÃ§Ã£o Ã  direita*/
        if (!(*balanceada)) {
            switch ((*nodo)->factor) {
                case NO_PESO_ESQUERDA:
                    (*nodo)->factor = NO_BALANCEADO;
                    *balanceada = 1;
                    break;
                case NO_BALANCEADO:
                    (*nodo)->factor = NO_PESO_DIREITA;
                    break;
                case NO_PESO_DIREITA:
                    rodardireita_ArvoreAVL(nodo);
                    *balanceada = 1;
            }
        }
    } else {
        *balanceada = 1;
        (*nodo)->numinsercoes++;
        return 1; /*JÃ¡ existe*/
    }

    return 0;
}

static NodoArvoreAVL novonodo_ArvoreAVL(const void *valor) {
    NodoArvoreAVL novonodo;

    novonodo = (NodoArvoreAVL) malloc(sizeof (struct NodoArvoreAVL_));
    if (novonodo == NULL)
        return NULL;

    novonodo->valor = (void*) valor;
    novonodo->factor = NO_BALANCEADO;
    novonodo->esquerda = NULL;
    novonodo->direita = NULL;
    novonodo->numinsercoes = 1;

    return novonodo;
}

static void rodaresquerda_ArvoreAVL(NodoArvoreAVL *nodo_a_rodar) {
    NodoArvoreAVL esquerda, neto;

    esquerda = (*nodo_a_rodar)->esquerda;

    if (esquerda->factor == NO_PESO_ESQUERDA) {
        (*nodo_a_rodar)->esquerda = esquerda->direita;
        esquerda -> direita = *nodo_a_rodar;
        (*nodo_a_rodar)-> factor = NO_BALANCEADO;
        esquerda->factor = NO_BALANCEADO;
        *nodo_a_rodar = esquerda;
    } else {
        neto = esquerda->direita;
        esquerda ->direita = neto->esquerda;
        neto->esquerda = esquerda;
        (*nodo_a_rodar)->esquerda = neto->direita;
        neto->direita = *nodo_a_rodar;

        switch (neto ->factor) {
            case NO_PESO_ESQUERDA:
                (*nodo_a_rodar)->factor = NO_PESO_DIREITA;
                esquerda ->factor = NO_BALANCEADO;
                break;

            case NO_BALANCEADO:
                (*nodo_a_rodar)->factor = NO_BALANCEADO;
                esquerda->factor = NO_BALANCEADO;
                break;
            case NO_PESO_DIREITA:
                (*nodo_a_rodar)->factor = NO_BALANCEADO;
                esquerda ->factor = NO_PESO_ESQUERDA;
                break;
        }
        neto ->factor = NO_BALANCEADO;
        *nodo_a_rodar = neto;
    }
}

static void rodardireita_ArvoreAVL(NodoArvoreAVL *nodo_a_rodar) {
    NodoArvoreAVL direita, neto;

    direita = (*nodo_a_rodar)->direita;

    if (direita->factor == NO_PESO_DIREITA) {
        (*nodo_a_rodar)->direita = direita->esquerda;
        direita -> esquerda = *nodo_a_rodar;
        (*nodo_a_rodar)-> factor = NO_BALANCEADO;
        direita->factor = NO_BALANCEADO;
        *nodo_a_rodar = direita;
    } else {
        neto = direita->esquerda;
        direita ->esquerda = neto->direita;
        neto->direita = direita;
        (*nodo_a_rodar)->direita = neto->esquerda;
        neto->esquerda = *nodo_a_rodar;

        switch (neto ->factor) {
            case NO_PESO_ESQUERDA:
                (*nodo_a_rodar)->factor = NO_BALANCEADO;
                direita ->factor = NO_PESO_DIREITA;
                break;

            case NO_BALANCEADO:
                (*nodo_a_rodar)->factor = NO_BALANCEADO;
                direita->factor = NO_BALANCEADO;
                break;
            case NO_PESO_DIREITA:
                (*nodo_a_rodar)->factor = NO_PESO_ESQUERDA;
                direita ->factor = NO_BALANCEADO;
                break;
        }
        neto ->factor = NO_BALANCEADO;
        *nodo_a_rodar = neto;
    }
}

CodigoArray TreeToString(ArvoreAVL tree) {
    CodigoArray a = newCA();
    a = treeTraversal_aux(tree->raiz, a);
    return a;
}

CodigoArray treeTraversal_aux(struct NodoArvoreAVL_* avl, CodigoArray ca) {
    CodigoArray aux = ca;
    if (avl) {
        aux = treeTraversal_aux(avl->esquerda, aux);
        aux = insert(aux, avl->valor);
        aux = treeTraversal_aux(avl->direita, aux);
    } else return aux;
}

void* get(ArvoreAVL tree, void* valor) {
    return get(tree->raiz, tree->compara, valor);
}

void* get(struct NodoArvoreAVL_* tree, int (*compara) (const void *valor1, const void *valor2), void* valor) {
    if (tree == NULL) return NULL;
    else if (compara(tree->valor, valor) > 0) return get(tree->esquerda, compara, valor);
    else if (compara(tree->valor, valor) < 0) return get(tree->direita, compara, valor);
    else if (compara(tree->valor, valor) == 0) return tree;
}

NodoArvoreAVL getTree(ArvoreAVL tree) {
    return tree->raiz;
}

Table constroiTabela(ArvoreAVL arvore) {
    Table table = newTab();
    table = constroiTabela_aux(arvore->raiz, table);
    return table;
}

static Table constroiTabela_aux(NodoArvoreAVL nodo, Table tab) {
    int i;
    Table aux = tab;
    if (nodo != NULL) {
        if (strcmp(Cli_getCodigo(((Cliente) nodo->valor)), tab->codigo) > 0) aux = constroiTabela_aux(nodo->esquerda, aux);
        else if (strcmp(Cli_getCodigo(((Cliente) nodo->valor)), tab->codigo) < 0) aux = constroiTabela_aux(nodo->direita, aux);
        else if (strcmp(Cli_getCodigo(((Cliente) nodo->valor)), tab->codigo) == 0) {
            for (i = 1; i <= 12; i++)
                aux = Tab_addValor(aux, Cli_getCompras(nodo->valor, i), i);
        }
    }
    else return aux;
}

Par procuraClientesSemCompras(ArvoreAVL arvore, Par p) {
    Par aux = p;
    aux = procuraClientesSemCompras_aux(arvore->raiz, aux);
    return aux;
}

static Par procuraClientesSemCompras_aux(NodoArvoreAVL avl, Par p) {
    Par aux = p;
    if (avl != NULL) {
        if (Cli_getNCompras(((Cliente) avl->valor)) == 0) aux = Par_addCliente(aux);
        aux = procuraClientesSemCompras_aux(avl->esquerda, aux);
        aux = procuraClientesSemCompras_aux(avl->direita, aux);
    } else return aux;
}

Par procuraProdutosNaoComprados(ArvoreAVL arvore, Par p) {
    Par aux = p;
    aux = procuraProdutosNaoComprados_aux(arvore->raiz, aux);
    return aux;
}

static Par procuraProdutosNaoComprados_aux(NodoArvoreAVL avl, Par p) {
    Par aux = p;
    if (avl != NULL) {
        if (Prod_getNVezesComprado(((Produto) avl->valor)) == 0) aux = Par_addProduto(aux);
        aux = procuraProdutosNaoComprados_aux(avl->esquerda, aux);
        aux = procuraProdutosNaoComprados_aux(avl->direita, aux);
    } else return aux;
}

CodigoArray compraTodos(ArvoreAVL avl) {
    CodigoArray ca = newCA();
    ca = compraTodos_aux(avl->raiz, ca);
    return ca;
}

static CodigoArray compraTodos_aux(NodoArvoreAVL avl, CodigoArray ca) {
    CodigoArray aux = ca;
    if (avl != NULL) {
        Cliente cl = avl->valor;
        if (Cli_compraEmTodosOsMeses(cl)) aux = insert(aux, Cli_getCodigo(cl));
        aux = compraTodos_aux(avl->esquerda, aux);
        aux = compraTodos_aux(avl->direita, aux);
    }
    else return aux;
}

ArvoreQtd constroiArvore(ArvoreAVL avl) {
    ArvoreQtd aq = newAQ();
    aq = constroiArvore_aux(avl->raiz, aq);
    return aq;
}

static ArvoreQtd constroiArvore_aux(NodoArvoreAVL nodo, ArvoreQtd aq) {
    ArvoreQtd aux = aq;
    if (nodo != NULL) {
        Produto p = nodo->valor;
        aux = insert(aux, Prod_getCodigo(p), Prod_getQuantidadeComprada(p));
        aux = constroiArvore_aux(nodo->esquerda, aux);
        aux = constroiArvore_aux(nodo->direita, aux);
    }
    return aux;
}

TabelaCSV carregaClientes(ArvoreAVL avl, TabelaCSV csv) {
    return carregaClientes_aux(avl->raiz, csv);
}

static TabelaCSV carregaClientes_aux(NodoArvoreAVL avl, TabelaCSV csv) {
    TabelaCSV aux = csv;
    if (avl) {
        aux = CDB_carregaCliente((Cliente) avl->valor, aux);
        aux = carregaClientes_aux(avl->esquerda, aux);
        aux = carregaClientes_aux(avl->direita, aux);
    } else return aux;
}

ArvoreQtd constroiArvoreQtd(ArvoreAVL avl) {
    ArvoreQtd auxil = newAQ();
    return constroiArvoreQtd_aux(avl->raiz, auxil);
}

static ArvoreQtd constroiArvoreQtd_aux(NodoArvoreAVL nodo, ArvoreQtd aq) {
    ArvoreQtd aux = aq;
    if (nodo) {
        Produto p = nodo->valor;
        aux = insert(aux, Prod_getCodigo(p), Prod_getQuantidadeComprada(p));
        aux = constroiArvoreQtd_aux(nodo->esquerda, aux);
        aux = constroiArvore_aux(nodo->direita, aux);
    } else return aux;
}