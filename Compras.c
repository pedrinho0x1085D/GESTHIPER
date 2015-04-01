
#include "AVLTree.h"
#include "Compras.h"
#include "Codigo.h"
#include <string.h>

static void compradoresTraversal(struct simpleCli* comps, CodigoArray ca);
static void produtosTraversal(struct simpleProd* comps, CodigoArray ca);

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

struct produto{
    char* codigo;
    struct simpleCli* cliCompradores;
    int nVezesComprado;
};

struct simpleProd {
    char* codigo;
    int qtdCompradaTotal;
    int qtdCompN, qtdCompP;
    float valorTotal;
    float valorN,valorP;
    struct simpleProd *left,*right;
};

struct produto{
    char* codigo;
    struct simpleCli* cliCompradores;
    int nVezesComprado;
};

struct simpleCli{
    char* codigo;
    int qtdCompradaTotal;
    int qtdCompN, qtdCompP;
    float valorTotal;
    float valorN,valorP;
    struct simpleProd *left,*right;
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
ClienteTree new(){
    ClienteTree aux=malloc(sizeof(struct clienteTree));
    aux->arvore=cria_ArvoreAVL(&comparatorCliente,&destroi);
    return aux;
}

ProdutoTree new(){
    ProdutoTree aux=malloc(sizeof(struct produtoTree));
    aux->arvore=cria_ArvoreAVL(&comparatorProduto,&destroi);
    return aux;
}


void insert(CompraTree ct, Compra c) {
    insere_ArvoreAVL(ct->arvore, c);
}
void insert(CompraTree ct, char* codigoP,float valorUni, int quantidade,char modo,char* codigoC,int mes){
    Compra c=new(codigoP,valorUni,quantidade,modo,codigoC,mes);
    insere_ArvoreAVL(ct->arvore,c);
}
/*Ver  se esta uma javardice ou não*/
void insert(ClienteTree ct, Cliente c){
    insere_ArvoreAVL(ct->arvore, c);
}
void insert(ClienteTree ct,char* codigoC){
    Cliente c =new(codigoC);
    insere_ArvoreAVL(ct->arvore,c);
}
void insert(ProdutoTree pt, Produto p){
    insere_ArvoreAVL(pt->arvore, p);
}
void insert(ProdutoTree pt, char* codigoP){
    Produto p = new(codigoP);
    insere_ArvoreAVL(pt->arvore, p);
}
/* ################################# */
Produto new(char* codigo){
    Produto aux=malloc(sizeof(struct produto));
    aux->codigo=strdup(codigo);
    aux->cliCompradores=NULL;
    aux->nVezesComprado=0;
    return aux;
}
char* getCodigo(Produto p){
    return strdup(p->codigo);
}
int getNVezesComprado(Produto p){
    return p->nVezesComprado;
}
CodigoArray getCliCompradores(Produto p){
    CodigoArray a=new();
    compradoresTraversal(p->cliCompradores,a);
    return a;
}

void compradoresTraversal(struct simpleCli* comps, CodigoArray ca){
    if(comps){
        compradoresTraversal(comps->left,ca);
        insert(ca,comps->codigo);
        compradoresTraversal(comps->right,ca);
    }
}
Cliente new(char* codigo){
    Cliente aux=malloc(sizeof(struct cliente));
    aux->codigo=strdup(codigo);
    aux->prodComprados=NULL;
    aux->nCompras=0;
    return aux;
}

char* getCodigo(Cliente c){
    return strdup(c->codigo);
}
int getNVezesComprado(Cliente c){
    return c->nCompras;
}
CodigoArray getProdComprados(Cliente c){
    CodigoArray a=new();
    produtosTraversal(c->prodComprados,a);
    return a;
}

void produtosTraversal(struct simpleProd* comps, CodigoArray ca){
    if(comps){
        compradoresTraversal(comps->left,ca);
        insert(ca,comps->codigo);
        compradoresTraversal(comps->right,ca);
    }
}

int comparatorCliente(const Cliente valor1, const Cliente valor2) {
    return strcmp(valor1->codigo,valor2->codigo);    
}

int comparatorProduto(const Produto valor1, const Produto valor2) {
    return strcmp(valor1->codigo,valor2->codigo);
}

struct produtoTree{
    ArvoreAVL arvore;
};

struct clienteTree{
    ArvoreAVL arvore;
};

ClienteTree new(){
    ClienteTree aux=malloc(sizeof(struct clienteTree));
    aux->arvore=cria_ArvoreAVL(&comparatorCliente,&destroi);
    return aux;
}

ProdutoTree new(){
    ProdutoTree aux=malloc(sizeof(struct produtoTree));
    aux->arvore=cria_ArvoreAVL(&comparatorProduto,&destroi);
    return aux;
}
