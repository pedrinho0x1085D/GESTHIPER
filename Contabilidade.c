#include "CusTypes.h"
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "AVLTree.h"
#include "Contabilidade.h"
#include "EstruturasAux.h"
#include <ctype.h>
#define ALFABETO 27

struct contnode_ {
    Codigo codigo;
    int vendasN[12], vendasP[12];
    int NVendN[12], NVendP[12];
    float faturaN[12], faturaP[12];
    struct contnode_ *left, *right;
};

struct arvoreContabil {
    Contab arvores[27];
};

Contab newCont(Codigo codigo) {
    Contab aux = malloc(sizeof (struct contnode_));
    int i;
    aux->codigo = strdup(codigo);
    for (i = 0; i < 12; i++) {
        aux->faturaN[i] = 0;
        aux->faturaP[i] = 0;
        aux->vendasN[i] = 0;
        aux->vendasP[i] = 0;
        aux->NVendN[i] = 0;
        aux->NVendP[i] = 0;
        aux->left = NULL;
        aux->right = NULL;
    }
    return aux;
}

int hashFuncCont(Codigo codigo) {
    char firstletter;

    firstletter = toupper(codigo[0]) - 'A' + 1;
    if ((firstletter < 0) || (firstletter > 26))
        firstletter = 0;

    return (int) firstletter;
}

CTree CT_insert(CTree ct, Codigo codigo) {
    CTree aux = ct;
    int pos = hashFuncCont(codigo);
    aux->arvores[pos] = Cont_insert(aux->arvores[pos], codigo);
    return aux;
}

Contab Cont_insert(Contab cont, Codigo codigo) {
    Contab aux = cont;
    if (aux == NULL) {
        aux = newCont(codigo);
    } else if (strcmp(aux->codigo, codigo) > 0) Cont_insert(aux->left, codigo);
    else if (strcmp(aux->codigo, codigo) < 0) Cont_insert(aux->right, codigo);
    return aux;
}

CTree newCT() {
    int i;
    CTree aux = malloc(sizeof (struct arvoreContabil));
    for (i = 0; i < 27; i++)
        aux->arvores[i] = NULL;
    return aux;
}

void CT_dispose(CTree nodo) {
    int i;
    if (nodo != NULL) {
        for (i = 0; i < 27; i++) {
            Cont_dispose(nodo->arvores[i]);
        }
        free(nodo);
    }
}

void Cont_dispose(Contab nodo) {
    if (nodo == NULL) return;
    if (nodo->left != NULL) Cont_dispose(nodo->left);
    if (nodo->right != NULL) Cont_dispose(nodo->right);
    free(nodo->codigo);
    free(nodo->faturaN);
    free(nodo->faturaP);
    free(nodo->vendasN);
    free(nodo->vendasP);
    free(nodo);
}

CTree CT_insereCompra(CTree ct, Codigo codigo, char modo, int qtd, float valor, int mes) {
    CTree aux = ct;
    int pos = hashFuncCont(codigo);
    aux->arvores[pos] = Cont_insereCompra(aux->arvores[pos], codigo, modo, qtd, valor, mes);
    return aux;
}

Contab Cont_insereCompra(Contab c, Codigo codigo, char modo, int qtd, float valor, int mes) {
    Contab aux = c;
    if (aux == NULL) {
        aux = newCont(codigo);
        if (modo == 'N') {
            aux->vendasN[mes - 1] += qtd;
            aux->faturaN[mes - 1] += (qtd * valor);
            aux->NVendN[mes - 1]++;
        } else if (modo == 'P') {
            aux->vendasP[mes - 1] += qtd;
            aux->faturaP[mes - 1] += (qtd * valor);
            aux->NVendP[mes - 1]++;
        }
    } else if (strcmp(aux->codigo, codigo) > 0) Cont_insereCompra(aux->left, codigo, modo, qtd, valor, mes);
    else if (strcmp(aux->codigo, codigo) < 0) Cont_insereCompra(aux->right, codigo, modo, qtd, valor, mes);
    else if (strcmp(aux->codigo, codigo) == 0) {
        if (modo == 'N') {
            aux->vendasN[mes - 1] += qtd;
            aux->faturaN[mes - 1] += (qtd * valor);
            aux->NVendN[mes - 1]++;
        } else if (modo == 'P') {
            aux->vendasP[mes - 1] += qtd;
            aux->faturaP[mes - 1] += (qtd * valor);
            aux->NVendP[mes - 1]++;
        }

    }
    return aux;
}

float CT_getFaturacaoNormal(CTree ct, Codigo codigo, int mes) {
    int pos = hashFuncCont(codigo);
    return Cont_getFaturacaoNormal(ct->arvores[pos], codigo, mes);
}

float Cont_getFaturacaoNormal(Contab c, Codigo codigo, int mes) {
    if (c == NULL) return -1; /*Non Existent Code*/
    else if (strcmp(c->codigo, codigo) > 0) return Cont_getFaturacaoNormal(c->left, codigo, mes);
    else if (strcmp(c->codigo, codigo) < 0) return Cont_getFaturacaoNormal(c->right, codigo, mes);
    else if (strcmp(c->codigo, codigo) == 0) return c->faturaN[mes - 1];
    return 0;
}

float CT_getFaturacaoPromo(CTree ct, Codigo codigo, int mes) {
    int pos = hashFuncCont(codigo);
    return Cont_getFaturacaoPromo(ct->arvores[pos], codigo, mes);
}

float Cont_getFaturacaoPromo(Contab c, Codigo codigo, int mes) {
    if (c == NULL) return -1; /*Non Existent Code*/
    else if (strcmp(c->codigo, codigo) > 0) return Cont_getFaturacaoPromo(c->left, codigo, mes);
    else if (strcmp(c->codigo, codigo) < 0) return Cont_getFaturacaoPromo(c->right, codigo, mes);
    else if (strcmp(c->codigo, codigo) == 0) return c->faturaP[mes - 1];
    return 0;
}

int CT_getVendasNormal(CTree ct, Codigo codigo, int mes) {
    int pos = hashFuncCont(codigo);
    return Cont_getVendasNormal(ct->arvores[pos], codigo, mes);
    return 0;
}

Boolean Cont_naoCompradoNoAno(Contab ct) {
    int i;
    Boolean flag = TRUE;
    for (i = 0; i < 12 && flag; i++)
        if (ct->NVendN[i] + ct->NVendP[i] != 0) flag = FALSE;
    return flag;

}

int Cont_getVendasNormal(Contab c, Codigo codigo, int mes) {
    if (c == NULL) return -1; /*Non Existent Code*/
    else if (strcmp(c->codigo, codigo) > 0) return Cont_getVendasNormal(c->left, codigo, mes);
    else if (strcmp(c->codigo, codigo) < 0) return Cont_getVendasNormal(c->right, codigo, mes);
    else if (strcmp(c->codigo, codigo) == 0) return c->vendasN[mes - 1];
    return 0;
}

int CT_getVendasPromo(CTree ct, Codigo codigo, int mes) {
    int pos = hashFuncCont(codigo);
    return Cont_getVendasPromo(ct->arvores[pos], codigo, mes);
}

int Cont_getVendasPromo(Contab c, Codigo codigo, int mes) {
    if (c == NULL) return -1; /*Non Existent Code*/
    else if (strcmp(c->codigo, codigo) > 0) return Cont_getVendasPromo(c->left, codigo, mes);
    else if (strcmp(c->codigo, codigo) < 0) return Cont_getVendasPromo(c->right, codigo, mes);
    else if (strcmp(c->codigo, codigo) == 0) return c->vendasP[mes - 1];
    return 0;
}

int CT_getNVendasNormal(CTree ct, Codigo codigo, int mes) {
    int pos = hashFuncCont(codigo);
    return Cont_getNVendasNormal(ct->arvores[pos], codigo, mes);
}

int Cont_getNVendasNormal(Contab c, Codigo codigo, int mes) {
    if (c == NULL) return -1; /*Non Existent Code*/
    else if (strcmp(c->codigo, codigo) > 0) return Cont_getNVendasNormal(c->left, codigo, mes);
    else if (strcmp(c->codigo, codigo) < 0) return Cont_getNVendasNormal(c->right, codigo, mes);
    else if (strcmp(c->codigo, codigo) == 0) return c->NVendN[mes - 1];
    return 0;
}

int CT_getNVendasPromo(CTree ct, Codigo codigo, int mes) {
    int pos = hashFuncCont(codigo);
    return Cont_getNVendasPromo(ct->arvores[pos], codigo, mes);
}

int Cont_getNVendasPromo(Contab c, Codigo codigo, int mes) {
    if (c == NULL) return -1; /*Non Existent Code*/
    else if (strcmp(c->codigo, codigo) > 0) return Cont_getNVendasPromo(c->left, codigo, mes);
    else if (strcmp(c->codigo, codigo) < 0) return Cont_getNVendasPromo(c->right, codigo, mes);
    else if (strcmp(c->codigo, codigo) == 0) return c->NVendP[mes - 1];
    return 0;
}

VendasProduto CT_getDadosProduto(CTree ct, Codigo codigo, int mes) {
    int pos = hashFuncCont(codigo);
    return Cont_getDadosProduto(ct->arvores[pos], codigo, mes);
}

VendasProduto Cont_getDadosProduto(Contab c, Codigo codigo, int mes) {
    if (c == NULL) return newVP(0, 0, 0);
    else if (strcmp(c->codigo, codigo) > 0) return Cont_getDadosProduto(c->left, codigo, mes);
    else if (strcmp(c->codigo, codigo) < 0) return Cont_getDadosProduto(c->right, codigo, mes);
    else if (strcmp(c->codigo, codigo) == 0) return newVP((c->vendasN[mes - 1]), (c->vendasP[mes - 1]), (c->faturaN[mes - 1] + c->faturaP[mes - 1]));
    return 0;
}

TabelaCSV CT_carregaCompras(CTree ct, TabelaCSV csv) {
    int i;
    TabelaCSV aux = csv;

    for (i = 0; i < ALFABETO; i++) {
        aux = Cont_carregaCompras(ct->arvores[i], aux);
    }
    return aux;
}

TabelaCSV Cont_carregaCompras(Contab cont, TabelaCSV csv) {
    int i;
    TabelaCSV aux = csv;
    if (cont) {
        for (i = 0; i < 12; i++) {
            aux = CSV_addCompras(aux, i + 1, (cont->NVendN[i] + cont->NVendP[i]));
        }
        aux = Cont_carregaCompras(cont->left, aux);
        aux = Cont_carregaCompras(cont->right, aux);
    }
    return aux;
}

CodigoArray CT_produtosNaoComprados(CTree ct) {
    int i;
    CodigoArray aux = newCA();
    for (i = 0; i < ALFABETO; i++)
        aux = Cont_insereProdutosNaoComprados(ct->arvores[i], aux);
    return aux;
}

CodigoArray Cont_insereProdutosNaoComprados(Contab ct, CodigoArray ca) {
    CodigoArray aux = ca;
    if (ct) {
        if (Cont_naoCompradoNoAno(ct)) aux = CA_insert(aux, ct->codigo);
        aux = Cont_insereProdutosNaoComprados(ct->left, aux);
        aux = Cont_insereProdutosNaoComprados(ct->right, aux);
    } else return aux;
    return aux;
}

Faturacao CT_criaLista(CTree ct, int lower, int higher) {
    int i;
    Faturacao aux = newFat();
    for (i = 0; i < ALFABETO; i++)
        aux = Cont_carregaLista(ct->arvores[i], lower, higher, aux);
    return aux;
}

Faturacao Cont_carregaLista(Contab ct, int lower, int higher, Faturacao ft) {
    Faturacao aux = ft;
    int i;
    if (ct) {
        for (i = lower; i <= higher; i++)
            aux = Fat_insereCompra(aux, (ct->faturaN[i - 1] + ct->faturaP[i - 1]), (ct->vendasN[i - 1] + ct->vendasP[i - 1]));
        aux = Cont_carregaLista(ct->left, lower, higher, aux);
        aux = Cont_carregaLista(ct->right, lower, higher, aux);
    } else return aux;
    return aux;
}
