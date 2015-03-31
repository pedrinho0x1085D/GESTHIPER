
#include "AVLTree.h"
#include "Compras.h"
#include <string.h>

struct compra {
    char* codigoP;
    float valorUni;
    int quantidade;
    char modo;
    char* codigoC;
    int mes;
};
struct cliente{
    char* codigo;
    struct simpleProd* prodComprados;
    int nCompras;

};

struct simpleProd {
    char* codigo;
    int qtdCompradaTotal;
    int qtdCompN, qtdCompP;
    float valorTotal;
    float valorN,valorP;
    struct simpleProd* left,*right;
};

struct produto{
    char* codigo;
    struct simpleCli* cliCompradores;
    int nVezesComprado;
};



Compra new(char* codigoP, float valorUni, int quantidade, char modo, char* codigoC, int mes) {
    Compra aux = malloc(sizeof (struct compra));
    aux->codigoP = strdup(codigoP);
    aux->valorUni = valorUni;
    aux->quantidade = quantidade;
    aux->modo = modo;
    aux->codigoC = strdup(codigoC);
    aux->mes = mes;
    return aux;
}

char* getCodigoP(Compra com) {
    return strdup(com->codigoP);
}

float getValorUni(Compra com) {
    return com->valorUni;
}

int getQuantidade(Compra com) {
    return com->quantidade;
}

char getModo(Compra com) {
    return com->modo;
}

char* getCodigoC(Compra com) {
    return strdup(com->codigoC);
}

int getMes(Compra com) {
    return com->mes;
}

int equals(Compra c1, Compra c2) {
    int ch1, ch2, ch3, ch4, ch5, ch6;
    ch1 = strcmp(c1->codigoP, c2->codigoP);
    ch2 = c1->valorUni - c2->valorUni;
    ch3 = c1->quantidade - c2->quantidade;
    ch4 = c1->modo - c2->modo;
    ch5 = strcmp(c1->codigoC, c2->codigoC);
    ch6 = c1->mes - c2->mes;
    return !(ch1 || ch2 || ch3 || ch4 || ch5 || ch6);
}

int comparatorCompra(const Compra valor1, const Compra valor2) {
    int i;
    if (valor1->mes != valor2->mes) return valor1->mes - valor2->mes;
    else if (i = (strcmp(valor1->codigoP, valor2->codigoP))) return i;
    else if (i = (strcmp(valor1->codigoP, valor2->codigoP))) return i;
    else return -1;
}

void destroi(void* valor1) {
    free(valor1);
}

struct compratree {
    ArvoreAVL arvore;
};

CompraTree new() {
    CompraTree aux = malloc(sizeof (struct compratree));
    aux->arvore = cria_ArvoreAVL(&comparatorCompra, &destroi);
}

void insert(CompraTree ct, Compra c) {
    insere_ArvoreAVL(ct->arvore, c);
}
void insert(CompraTree ct, char* codigoP,float valorUni, int quantidade,char modo,char* codigoC,int mes){
    Compra c=new(codigoP,valorUni,quantidade,modo,codigoC,mes);
    insere_ArvoreAVL(ct->arvore,c);
}
/*
struct cliente{
    char* codigo;
    struct simpleProd* prodComprados;
    int nCompras;

};



 */
