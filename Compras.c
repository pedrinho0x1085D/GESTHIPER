
#include "AVLTree.h"
#include "Compras.h"
#include "EstruturasAux.h"
#include <string.h>
#include "CusTypes.h"

static void compradoresTraversal(struct simpleCli* comps, CodigoArray ca);
static void produtosTraversal(struct simpleProd* comps, CodigoArray ca);

struct compra {
    Codigo codigoP;
    float valorUni;
    int quantidade;
    char modo;
    Codigo codigoC;
    int mes;
};

struct cliente {
    Codigo codigo;
    int compraMes[12];
    struct simpleProd* prodComprados;
    int nCompras;

};

struct produto {
    Codigo codigo;
    struct simpleCli* cliCompradores;
    int nVezesComprado;
    int qtdComprada;
    int compradoMes[12];
};

struct simpleProd {
    Codigo codigo;
    int mes;
    int qtdCompradaTotal;
    int qtdCompN, qtdCompP;
    float valorTotal;
    float valorN, valorP;
    struct simpleProd *left, *right;
};

static struct simpleProd* new(Codigo codigo, int mes) {
    struct simpleProd* aux = malloc(sizeof (struct simpleProd));
    aux->codigo = strdup(codigo);
    aux->qtdCompradaTotal = aux->qtdCompN = aux->qtdCompP = 0;
    aux->valorN = aux->valorP = aux->valorTotal = 0;
    aux->mes = mes;
    aux->left = aux->right = NULL;
    return aux;
}

struct simpleCli {
    Codigo codigo;
    int mes;
    int qtdCompradaTotal;
    int qtdCompN, qtdCompP;
    float valorTotal;
    float valorN, valorP;
    struct simpleProd *left, *right;
};

static struct simpleCli* new(Codigo codigo, int mes) {
    struct simpleCli* aux = malloc(sizeof (struct simpleCli));
    aux->codigo = strdup(codigo);
    aux->qtdCompradaTotal = aux->qtdCompN = aux->qtdCompP = 0;
    aux->valorN = aux->valorP = aux->valorTotal = 0;
    aux->mes = mes;
    aux->left = aux->right = NULL;
    return aux;
}

Compra new(Codigo codigoP, float valorUni, int quantidade, char modo, Codigo codigoC, int mes) {
    Compra aux = malloc(sizeof (struct compra));
    aux->codigoP = strdup(codigoP);
    aux->valorUni = valorUni;
    aux->quantidade = quantidade;
    aux->modo = modo;
    aux->codigoC = strdup(codigoC);
    aux->mes = mes;
    return aux;
}

Codigo getCodigoP(Compra com) {
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

Codigo getCodigoC(Compra com) {
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

ClienteTree new() {
    ClienteTree aux = malloc(sizeof (struct clienteTree));
    aux->arvore = cria_ArvoreAVL(&comparatorCliente, &destroi);
    return aux;
}

ProdutoTree new() {
    ProdutoTree aux = malloc(sizeof (struct produtoTree));
    aux->arvore = cria_ArvoreAVL(&comparatorProduto, &destroi);
    return aux;
}

CompraTree insert(CompraTree ct, Compra c) {
    CompraTree aux=ct;
    insere_ArvoreAVL(aux->arvore, c);
    return aux;
}

CompraTree insert(CompraTree ct, Codigo codigoP, float valorUni, int quantidade, char modo, Codigo codigoC, int mes) {
    CompraTree aux=ct;
    Compra c = new(codigoP, valorUni, quantidade, modo, codigoC, mes);
    insere_ArvoreAVL(aux->arvore, c);
    return aux;
}

ClienteTree insert(ClienteTree ct, Cliente c) {
    ClienteTree aux=ct;
    insere_ArvoreAVL(aux->arvore, c);
    return aux;
}

ClienteTree insert(ClienteTree ct, Codigo codigoC) {
    ClienteTree aux=ct;
    Cliente c = new(codigoC);
    insere_ArvoreAVL(aux->arvore, c);
    return aux;
}

ProdutoTree insert(ProdutoTree pt, Produto p) {
    ProdutoTree aux=pt;
    insere_ArvoreAVL(aux->arvore, p);
    return aux;
}

ProdutoTree insert(ProdutoTree pt, Codigo codigoP) {
    ProdutoTree aux=pt;
    Produto p = new(codigoP);
    insere_ArvoreAVL(aux->arvore, p);
    return aux;
}

Produto new(Codigo codigo) {
    int i = 0;
    Produto aux = malloc(sizeof (struct produto));
    aux->codigo = strdup(codigo);
    aux->cliCompradores = NULL;
    aux->nVezesComprado = 0;
    aux->qtdComprada=0;
    for (i = 0; i < 12; i++)
        aux->compradoMes[i] = 0;
    return aux;
}

Boolean compradoMes(Produto p,int mes){
    if (p->compradoMes[mes-1]) return 1;
    else return 0;
}
Boolean compraNoMes(Cliente c,int mes){
    if(c->compraMes[mes-1]) return 1;
    else return 0;
}
Codigo getCodigo(Produto p) {
    return strdup(p->codigo);
}

int getNVezesComprado(Produto p) {
    return p->nVezesComprado;
}

CodigoArray getCliCompradores(Produto p) {
    CodigoArray a = new();
    compradoresTraversal(p->cliCompradores, a);
    return a;
}

void compradoresTraversal(struct simpleCli* comps, CodigoArray ca) {
    if (comps) {
        compradoresTraversal(comps->left, ca);
        ca=insert(ca, comps->codigo);
        compradoresTraversal(comps->right, ca);
    }
}

Cliente new(Codigo codigo) {
    int i;
    Cliente aux = malloc(sizeof (struct cliente));
    aux->codigo = strdup(codigo);
    aux->prodComprados = NULL;
    aux->nCompras = 0;
    for (i = 0; i < 12; i++)
        aux->compraMes[i] = 0;
    return aux;
}

Codigo getCodigo(Cliente c) {
    return strdup(c->codigo);
}

int getNVezesComprado(Cliente c) {
    return c->nCompras;
}

CodigoArray getProdComprados(Cliente c) {
    CodigoArray a = new();
    produtosTraversal(c->prodComprados, a);
    return a;
}

int getCompras(Cliente c, int mes) {
    return c->compraMes[mes - 1];
}

int compraEmTodosOsMeses(Cliente c) {
    int i, flag = 1;
    for (i = 0; i < 12 && flag; i++)
        if (!(c->compraMes[i])) flag = 0;
    return flag;
}

int getVezesComprado(Produto p, int mes) {
    return p->compradoMes[mes - 1];
}

int compradoEmTodosOsMeses(Produto p) {
    int i, flag = 1;
    for (i = 0; i < 12 && flag; i++)
        if (!(p->compradoMes[i])) flag = 0;
    return flag;
}

void produtosTraversal(struct simpleProd* comps, CodigoArray ca) {
    if (comps) {
        compradoresTraversal(comps->left, ca);
        insert(ca, comps->codigo);
        compradoresTraversal(comps->right, ca);
    }
}

int comparatorCliente(const Cliente valor1, const Cliente valor2) {
    return strcmp(valor1->codigo, valor2->codigo);
}

int comparatorProduto(const Produto valor1, const Produto valor2) {
    return strcmp(valor1->codigo, valor2->codigo);
}

struct produtoTree {
    ArvoreAVL arvore;
};

struct clienteTree {
    ArvoreAVL arvore;
};

ClienteTree new() {
    ClienteTree aux = malloc(sizeof (struct clienteTree));
    aux->arvore = cria_ArvoreAVL(&comparatorCliente, &destroi);
    return aux;
}

ProdutoTree new() {
    ProdutoTree aux = malloc(sizeof (struct produtoTree));
    aux->arvore = cria_ArvoreAVL(&comparatorProduto, &destroi);
    return aux;
}

ProdutoTree updateProdTree(ProdutoTree pt, Codigo codigoP, int qtd, float valor, char modo, Codigo codigoC, int mes) {
    ProdutoTree aux=pt;
    Produto auxil = new(codigoP);
    Produto updat = get(aux->arvore, auxil);
    if (updat != NULL) {
        updat->nVezesComprado++;
        updat->compradoMes[mes - 1]++;
        updat->qtdComprada+=qtd;
        updat->cliCompradores=update(updat->cliCompradores, qtd, valor, modo, codigoC, mes);
    }
    return aux;
}

static struct simpleCli* update(struct simpleCli* sc, int qtd, float valor, char modo, Codigo codigoC, int mes) {
    struct simpleCli* aux=sc;
    if (aux == NULL) {
        aux = new(codigoC, mes);
        if (modo == 'N') {
            aux->qtdCompN += qtd;
            aux->valorN += (qtd * valor);

        } else if (modo == 'P') {
            aux->qtdCompP += qtd;
            aux->valorP += (qtd * valor);

        }
        aux->qtdCompradaTotal += qtd;
        aux->valorTotal += (qtd * valor);
    } else if (strcmp(aux->codigo, codigoC) > 0) aux->left=update(aux->left, qtd, valor, modo, codigoC, mes);
    else if (strcmp(aux->codigo, codigoC) < 0) aux->right=update(aux->right, qtd, valor, modo, codigoC, mes);
    else if (strcmp(aux->codigo, codigoC) == 0) {
        if (aux->mes > mes) aux->left=update(aux->left, qtd, valor, modo, codigoC, mes);
        else if (aux->mes < mes) aux->right=update(aux->right, qtd, valor, modo, codigoC, mes);
        else if (aux->mes == mes) {
            if (modo == 'N') {
                aux->qtdCompN += qtd;
                aux->valorN += (qtd * valor);
            } else if (modo == 'P') {
                aux->qtdCompP += qtd;
                aux->valorP += (qtd * valor);
            }
            aux->qtdCompradaTotal += qtd;
            aux->valorTotal += (qtd * valor);
        }
    }
    return aux;
}

ClienteTree updateCliTree(ClienteTree ct, Codigo codigoP, int qtd, float valor, char modo, Codigo codigoC, int mes) {
    ClienteTree aux=ct;
    Cliente auxil = new(codigoC);
    Cliente updat = get(ct->arvore, auxil);
    if (updat != NULL) {
        updat->nCompras++;
        updat->compraMes[mes - 1]++;
        updat->prodComprados=update(updat->prodComprados, qtd, valor, modo, codigoP, mes);
    }
    return aux;
}

static struct simpleProd* update(struct simpleProd* sp, int qtd, float valor, char modo, Codigo codigoP, int mes) {
    struct simpleProd* aux=sp;
    if (aux == NULL) {
        aux = new(codigoP, mes);
        if (modo == 'N') {
            aux->qtdCompN += qtd;
            aux->valorN += (qtd * valor);
        } else if (modo == 'P') {
            aux->qtdCompP += qtd;
            aux->valorP += (qtd * valor);
        }
        aux->qtdCompradaTotal += qtd;
        aux->valorTotal += (qtd * valor);
    } else if (strcmp(aux->codigo, codigoP) > 0) aux->left=update(aux->left, qtd, valor, modo, codigoP, mes);
    else if (strcmp(aux->codigo, codigoP) < 0) aux->right=update(aux->right, qtd, valor, modo, codigoP, mes);
    else if (strcmp(aux->codigo, codigoP) == 0) {
        if (aux->mes > mes) aux->left=update(aux->left, qtd, valor, modo, codigoP, mes);
        else if (aux->mes < mes) aux->right=update(aux->right, qtd, valor, modo, codigoP, mes);
        else if (aux->mes == mes) {
            if (modo == 'N') {
                aux->qtdCompN += qtd;
                aux->valorN += (qtd * valor);
            } else if (modo == 'P') {
                aux->qtdCompP += qtd;
                aux->valorP += (qtd * valor);
            }
            aux->qtdCompradaTotal += qtd;
            aux->valorTotal += (qtd * valor);
        }
    }
    return aux;
}

struct comprasDB {
    CompraTree compras;
    ClienteTree clientes;
    ProdutoTree produtos;
};

ComprasDB new() {
    ComprasDB aux = malloc(sizeof (struct comprasDB));
    aux->clientes = new();
    aux->compras = new();
    aux->produtos = new();
    return aux;
}

ComprasDB insertCliente(ComprasDB cdb, Codigo codigoC) {
    ComprasDB aux=cdb;
    aux->clientes=insert(aux->clientes, codigoC);
    return aux;
}

ComprasDB insertProduto(ComprasDB cdb, Codigo codigoP) {
    ComprasDB aux=cdb;
    aux->produtos=insert(aux->produtos, codigoP);
    return aux;
}

ComprasDB registerSale(ComprasDB cdb, Codigo codigoP, float valor, int qtd, char modo, Codigo codigoC, int mes) {
    ComprasDB aux=cdb;
    aux->compras=insert(aux->compras, codigoP, valor, qtd, modo, codigoC, mes);
    aux->produtos=updateProdTree(aux->produtos, codigoP, qtd, valor, modo, codigoC, mes);
    aux->clientes=updateCliTree(aux->clientes, codigoP, qtd, valor, modo, codigoC, mes);
    return aux;
}

void dispose(ComprasDB cdb) {
    dispose(cdb->clientes);
    dispose(cdb->compras);
    dispose(cdb->produtos);
    free(cdb);
}

void dispose(ClienteTree ct) {
    destroi_ArvoreAVL(ct->arvore);
    free(ct);
}

void dispose(ProdutoTree pt) {
    destroi_ArvoreAVL(pt->arvore);
    free(pt);
}

void dispose(CompraTree ct) {
    destroi_ArvoreAVL(ct->arvore);
    free(ct);
}

TabelaCSV carregaClientes(ComprasDB cdb,TabelaCSV csv){
    TabelaCSV aux=csv;
    aux=carregaClientes(cdb->clientes->arvore,aux);
    return aux;
}

TabelaCSV carregaCliente(TabelaCSV csv,Cliente cli){
    int i;
    TabelaCSV aux=csv;
    for(i=1;i<=12;i++)
        if(compraNoMes(cli,i)) aux=addCliente(aux,i);
    return aux;
}