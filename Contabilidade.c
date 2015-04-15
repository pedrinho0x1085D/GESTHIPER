#include <stdlib.h>
#include "AVLTree.h"
#include "Contabilidade.h"
#include "EstruturasAux.h"
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

/*Copiei estas duas do catalog.c nao sei se é só isto*/
int comparaCompra(const Contab valor1, const Contab valor2) {
    return strcmp((Codigo) valor1->codigo, (Codigo) valor2->codigo);
}

void destroi(void* valor1) {
    free(valor1);
}

Contab new() {
    return NULL;
}

Contab new(Codigo codigo) {
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

static int hashFunc(Codigo codigo) {
    char firstletter;

    firstletter = toupper(codigo[0]) - 'A' + 1;
    if ((firstletter < 0) || (firstletter > 26))
        firstletter = 0;

    return (int) firstletter;
}

CTree insert(CTree ct, Codigo codigo) {
    CTree aux = ct;
    int pos = hashFunc(codigo);
    aux->arvores[pos] = insert(aux->arvores[pos], codigo);
    return aux;
}

Contab insert(Contab cont, Codigo codigo) {
    Contab aux = cont;
    if (aux == NULL) {
        aux = new(codigo);
    } else if (strcmp(aux->codigo, codigo) > 0) insert(aux->left, codigo);
    else if (strcmp(aux->codigo, codigo) < 0) insert(aux->right, codigo);
    return aux;
}

CTree new() {
    int i;
    CTree aux = malloc(sizeof (struct arvoreContabil));
    for (i = 0; i < 27; i++)
        aux->arvores[i] = NULL;
    return aux;
}

void dispose(CTree nodo) {
    int i;
    if (nodo != NULL) {
        for (i = 0; i < 27; i++) {
            dispose(nodo->arvores[i]);
        }
        free(nodo);
    }
}

void dispose(Contab nodo) {
    if (nodo == NULL) return;
    if (nodo->left != NULL) dispose(nodo->left);
    if (nodo->right != NULL) dispose(nodo->right);
    free(nodo->codigo);
    free(nodo->faturaN);
    free(nodo->faturaP);
    free(nodo->vendasN);
    free(nodo->vendasP);
    free(nodo);
}

CTree insereCompra(CTree ct, Codigo codigo, char modo, int qtd, float valor, int mes) {
    CTree aux = ct;
    int pos = hashFunc(codigo);
    aux->arvores[pos] = insereCompra(aux->arvores[pos], codigo, modo, qtd, valor, mes);
    return aux;
}

Contab insereCompra(Contab c, Codigo codigo, char modo, int qtd, float valor, int mes) {
    Contab aux = c;
    if (aux == NULL) {
        aux = new(codigo);
        if (modo == 'N') {
            aux->vendasN[mes - 1] += qtd;
            aux->faturaN[mes - 1] += (qtd * valor);
            aux->NVendN[mes - 1]++;
        } else if (modo == 'P') {
            aux->vendasP[mes - 1] += qtd;
            aux->faturaP[mes - 1] += (qtd * valor);
            aux->NVendP[mes - 1]++;
        }
    } else if (strcmp(aux->codigo, codigo) > 0) insereCompra(aux->left, codigo, modo, qtd, valor, mes);
    else if (strcmp(aux->codigo, codigo) < 0) insereCompra(aux->right, codigo, modo, qtd, valor, mes);
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

float getFaturacaoNormal(CTree ct, Codigo codigo, int mes) {
    int pos = hashFunc(codigo);
    return getFaturacaoNormal(ct->arvores[pos], codigo, mes);
}

float getFaturacaoNormal(Contab c, Codigo codigo, int mes) {
    if (c == NULL) return -1; /*Non Existent Code*/
    else if (strcmp(c->codigo, codigo) > 0) return getFaturacaoNormal(c->left, codigo, mes);
    else if (strcmp(c->codigo, codigo) < 0) return getFaturacaoNormal(c->right, codigo, mes);
    else if (strcmp(c->codigo, codigo) == 0) return c->faturaN[mes - 1];
}

float getFaturacaoPromo(CTree ct, Codigo codigo, int mes) {
    int pos = hashFunc(codigo);
    return getFaturacaoPromo(ct->arvores[pos], codigo, mes);
}

float getFaturacaoPromo(Contab c, Codigo codigo, int mes) {
    if (c == NULL) return -1; /*Non Existent Code*/
    else if (strcmp(c->codigo, codigo) > 0) return getFaturacaoPromo(c->left, codigo, mes);
    else if (strcmp(c->codigo, codigo) < 0) return getFaturacaoPromo(c->right, codigo, mes);
    else if (strcmp(c->codigo, codigo) == 0) return c->faturaP[mes - 1];
}

int getVendasNormal(CTree ct, Codigo codigo, int mes) {
    int pos = hashFunc(codigo);
    return getVendasNormal(ct->arvores[pos], codigo, mes);
}

int getVendasNormal(Contab c, Codigo codigo, int mes) {
    if (c == NULL) return -1; /*Non Existent Code*/
    else if (strcmp(c->codigo, codigo) > 0) return getVendasNormal(c->left, codigo, mes);
    else if (strcmp(c->codigo, codigo) < 0) return getVendasNormal(c->right, codigo, mes);
    else if (strcmp(c->codigo, codigo) == 0) return c->vendasN[mes - 1];
}

int getVendasPromo(CTree ct, Codigo codigo, int mes) {
    int pos = hashFunc(codigo);
    return getVendasPromo(ct->arvores[pos], codigo, mes);
}

int getVendasPromo(Contab c, Codigo codigo, int mes) {
    if (c == NULL) return -1; /*Non Existent Code*/
    else if (strcmp(c->codigo, codigo) > 0) return getVendasPromo(c->left, codigo, mes);
    else if (strcmp(c->codigo, codigo) < 0) return getVendasPromo(c->right, codigo, mes);
    else if (strcmp(c->codigo, codigo) == 0) return c->vendasP[mes - 1];
}

int getNVendasNormal(CTree ct, Codigo codigo, int mes) {
    int pos = hashFunc(codigo);
    return getNVendasNormal(ct->arvores[pos], codigo, mes);
}

int getNVendasNormal(Contab c, Codigo codigo, int mes) {
    if (c == NULL) return -1; /*Non Existent Code*/
    else if (strcmp(c->codigo, codigo) > 0) return getNVendasNormal(c->left, codigo, mes);
    else if (strcmp(c->codigo, codigo) < 0) return getNVendasNormal(c->right, codigo, mes);
    else if (strcmp(c->codigo, codigo) == 0) return c->NVendN[mes - 1];
}

int getNVendasPromo(CTree ct, Codigo codigo, int mes) {
    int pos = hashFunc(codigo);
    return getNVendasPromo(ct->arvores[pos], codigo, mes);
}

int getNVendasPromo(Contab c, Codigo codigo, int mes) {
    if (c == NULL) return -1; /*Non Existent Code*/
    else if (strcmp(c->codigo, codigo) > 0) return getNVendasPromo(c->left, codigo, mes);
    else if (strcmp(c->codigo, codigo) < 0) return getNVendasPromo(c->right, codigo, mes);
    else if (strcmp(c->codigo, codigo) == 0) return c->NVendP[mes - 1];
}

AuxR2 getDadosProduto(CTree ct, Codigo codigo, int mes) {
    int pos = hashFunc(codigo);
    return getDadosProduto(ct->arvores[pos], codigo, mes);
}

static AuxR2 getDadosProduto(Contab c, Codigo codigo, int mes) {
    if (c == NULL) return new(0, 0, 0);
    else if (strcmp(c->codigo, codigo) > 0) return getDadosProduto(c->left, codigo, mes);
    else if (strcmp(c->codigo, codigo) < 0) return getDadosProduto(c->right, codigo, mes);
    else if (strcmp(c->codigo, codigo) == 0) return new((c->vendasN[mes - 1]), (c->vendasP[mes - 1]), (c->faturaN[mes - 1] + c->faturaP[mes - 1]));
}

TabelaCSV carregaCompras(CTree ct, TabelaCSV csv){
    int i;
    TabelaCSV aux=csv;
    for(i=0;i<ALFABETO;i++){
        aux=carregaCompras(ct->arvores[i],aux);
    }
    return aux;
}

TabelaCSV carregaCompras(Contab cont, TabelaCSV csv){
    int i;
    TabelaCSV aux=csv;
    if(cont){
        for(i=0;i<12;i++){
            aux=addCompra(aux,i+1,(cont->NVendN[i]+cont->NVendP[i]));
        }
        aux=carregaCompras(cont->left,aux);
        aux=carregaCompras(cont->right,aux);
    }
}