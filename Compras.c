
#include "AVLTree.h"
#include "Compras.h"
#include "Codigo.h"
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

void insert(CompraTree ct, Compra c) {
    insere_ArvoreAVL(ct->arvore, c);
}

void insert(CompraTree ct, Codigo codigoP, float valorUni, int quantidade, char modo, Codigo codigoC, int mes) {
    Compra c = new(codigoP, valorUni, quantidade, modo, codigoC, mes);
    insere_ArvoreAVL(ct->arvore, c);
}

void insert(ClienteTree ct, Cliente c) {
    insere_ArvoreAVL(ct->arvore, c);
}

void insert(ClienteTree ct, Codigo codigoC) {
    Cliente c = new(codigoC);
    insere_ArvoreAVL(ct->arvore, c);
}

void insert(ProdutoTree pt, Produto p) {
    insere_ArvoreAVL(pt->arvore, p);
}

void insert(ProdutoTree pt, Codigo codigoP) {
    Produto p = new(codigoP);
    insere_ArvoreAVL(pt->arvore, p);
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
        insert(ca, comps->codigo);
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

void updateProdTree(ProdutoTree pt, Codigo codigoP, int qtd, float valor, char modo, Codigo codigoC, int mes) {
    Produto auxil = new(codigoP);
    Produto updat = get(pt->arvore, auxil);
    if (updat != NULL) {
        updat->nVezesComprado++;
        updat->compradoMes[mes - 1]++;
        updat->qtdComprada+=qtd;
        update(updat->cliCompradores, qtd, valor, modo, codigoC, mes);
    }
}

static void update(struct simpleCli* sc, int qtd, float valor, char modo, Codigo codigoC, int mes) {
    if (sc == NULL) {
        sc = new(codigoC, mes);
        if (modo == 'N') {
            sc->qtdCompN += qtd;
            sc->valorN += (qtd * valor);

        } else if (modo == 'P') {
            sc->qtdCompP += qtd;
            sc->valorP += (qtd * valor);

        }
        sc->qtdCompradaTotal += qtd;
        sc->valorTotal += (qtd * valor);
    } else if (strcmp(sc->codigo, codigoC) > 0) update(sc->left, qtd, valor, modo, codigoC, mes);
    else if (strcmp(sc->codigo, codigoC) < 0) update(sc->right, qtd, valor, modo, codigoC, mes);
    else if (strcmp(sc->codigo, codigoC) == 0) {
        if (sc->mes > mes) update(sc->left, qtd, valor, modo, codigoC, mes);
        else if (sc->mes < mes) update(sc->right, qtd, valor, modo, codigoC, mes);
        else if (sc->mes == mes) {
            if (modo == 'N') {
                sc->qtdCompN += qtd;
                sc->valorN += (qtd * valor);
            } else if (modo == 'P') {
                sc->qtdCompP += qtd;
                sc->valorP += (qtd * valor);
            }
            sc->qtdCompradaTotal += qtd;
            sc->valorTotal += (qtd * valor);
        }
    }
}

void updateCliTree(ClienteTree ct, Codigo codigoP, int qtd, float valor, char modo, Codigo codigoC, int mes) {
    Cliente auxil = new(codigoC);
    Cliente updat = get(ct->arvore, auxil);
    if (updat != NULL) {
        updat->nCompras++;
        updat->compraMes[mes - 1]++;
        update(updat->prodComprados, qtd, valor, modo, codigoP, mes);
    }
}

static void update(struct simpleProd* sp, int qtd, float valor, char modo, Codigo codigoP, int mes) {
    if (sp == NULL) {
        sp = new(codigoP, mes);
        if (modo == 'N') {
            sp->qtdCompN += qtd;
            sp->valorN += (qtd * valor);
        } else if (modo == 'P') {
            sp->qtdCompP += qtd;
            sp->valorP += (qtd * valor);
        }
        sp->qtdCompradaTotal += qtd;
        sp->valorTotal += (qtd * valor);
    } else if (strcmp(sp->codigo, codigoP) > 0) update(sp->left, qtd, valor, modo, codigoP, mes);
    else if (strcmp(sp->codigo, codigoP) < 0) update(sp->right, qtd, valor, modo, codigoP, mes);
    else if (strcmp(sp->codigo, codigoP) == 0) {
        if (sp->mes > mes) update(sp->left, qtd, valor, modo, codigoP, mes);
        else if (sp->mes < mes) update(sp->right, qtd, valor, modo, codigoP, mes);
        else if (sp->mes == mes) {
            if (modo == 'N') {
                sp->qtdCompN += qtd;
                sp->valorN += (qtd * valor);
            } else if (modo == 'P') {
                sp->qtdCompP += qtd;
                sp->valorP += (qtd * valor);
            }
            sp->qtdCompradaTotal += qtd;
            sp->valorTotal += (qtd * valor);
        }
    }
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

void insertCliente(ComprasDB cdb, Codigo codigoC) {
    insert(cdb->clientes, codigoC);
}

void insertProduto(ComprasDB cdb, Codigo codigoP) {
    insert(cdb->produtos, codigoP);
}

void registerSale(ComprasDB cdb, Codigo codigoP, float valor, int qtd, char modo, Codigo codigoC, int mes) {
    insert(cdb->compras, codigoP, valor, qtd, modo, codigoC, mes);
    updateProdTree(cdb->produtos, codigoP, qtd, valor, modo, codigoC, mes);
    updateCliTree(cdb->clientes, codigoP, qtd, valor, modo, codigoC, mes);
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

CodigoArray nuncaComprados(ComprasDB cdb) {
    CodigoArray ca = new();
    nuncaComprados(cdb->produtos, ca);
    return ca;
}

struct tabela {
    Codigo codigo;
    int compras[12];
};

Table new(Codigo codigo) {
    int i;
    Table aux = malloc(sizeof (struct tabela));
    aux->codigo = strdup(codigo);
    for (i = 0; i < 12; i++)
        aux->compras[i] = 0;
    return aux;
}

void addValor(Table t, int qtd, int mes) {
    if (mes >= 1 && mes <= 12)
        t->compras[mes - 1] += qtd;
}

Codigo getCodigo(Table t) {
    return strdup(t->codigo);
}

int getCompras(Table t, int mes) {
    return t->compras[mes - 1];
}

void dispose(Table t) {
    free(t->codigo);
    free(t->compras);
    free(t);
}

void toTxtFile(Table t, char* filename) {
    int i;
    FILE* file = fopen(filename, "W");
    fprintf(file, "Codigo: %s\n", t->codigo);
    for (i = 0; i < 12; i++)
        fprintf(file, "Realizou %d compras no mes %d\n", t->compras[i], i + 1);
    fclose(file);
}

Table getTabelaCompras(ComprasDB dbc, Codigo codigo) {
    Table tab = new(codigo);
    constroiTabela(dbc->clientes->arvore, tab);
    return tab;
}

void constroiTabela(Cliente cli, Table tab) {
    constroiTabela(cli->prodComprados, tab);
}

static void constroiTabela(struct simpleProd* sp, Table tab) {
    if (sp != NULL) {
        addValor(tab, sp->qtdCompradaTotal, sp->mes);
        constroiTabela(sp->left, tab);
        constroiTabela(sp->right, tab);
    }
}

struct tableQ11 {
    int compras[12];
    int clientes[12];
};

TabelaCSV new() {
    TabelaCSV aux = malloc(sizeof (struct tableQ11));
    int i;
    for (i = 0; i < 12; i++) {
        aux->compras[i] = 0;
        aux->clientes[i] = 0;
    }
    return aux;
}

void add(TabelaCSV tcsv, int mes, int qtd) {
    tcsv->clientes[mes - 1]++;
    tcsv->compras[mes - 1] += qtd;
}

void dispose(TabelaCSV tcsv) {
    free(tcsv->clientes);
    free(tcsv->compras);
    free(tcsv);
}

TabelaCSV getRelacao(ComprasDB cdb) {
    TabelaCSV csv = new();
    getRelacao(cdb->compras->arvore, csv);
    return csv;
}

void toCsvFile(TabelaCSV csv, char* filename) {
    int i;
    FILE *file = fopen(strcat(filename, ".csv"), "W");
    fprintf(file, "\"Mês\",\"Compras\",\"Clientes\"\n");
    for (i = 0; i < 12; i++) {
        fprintf("\"%d\",\"%d\",\"%d\"\n", i + 1, csv->compras[i], csv->clientes[i]);
    }
    fclose(file);
}

struct par {
    int clientesSemCompras;
    int produtosNaoComprados;
};

Par new() {
    Par aux = malloc(sizeof (struct par));
    aux->clientesSemCompras = 0;
    aux->produtosNaoComprados = 0;
    return aux;
}

Par dispose(Par p) {
    free(p);
}

void addCliente(Par p) {
    p->clientesSemCompras++;
}

void addProduto(Par p) {
    p->produtosNaoComprados++;
}

int getClientesSemCompras(Par p) {
    return p->clientesSemCompras;
}

int getProdutosNaoComprados(Par p) {
    return p->produtosNaoComprados;
}

Par procuraNaoUtilizados(ComprasDB dbc) {
    Par p = new();
    procuraClientesSemCompras(dbc->clientes->arvore, p);
    procuraProdutosNaoComprados(dbc->produtos->arvore, p);
    return p;
}

int in(int x, int linf, int lsup) {
    return (x = >linf && x <= lsup);
}

struct auxilQ7 {
    int nCompras;
    float faturacao;
};

AuxQ7 new() {
    AuxQ7 aux = malloc(sizeof (struct auxilQ7));
    aux->faturacao = 0.0;
    aux->nCompras = 0;
    return aux;
}

void dispose(AuxQ7 aux) {
    free(aux);
}

float getFaturacao(AuxQ7 aux) {
    return aux->faturacao;
}

int getNCompras(AuxQ7 aux) {
    return aux->nCompras;
}

void insereCompra(AuxQ7 auxil, float valor, int qtd) {
    auxil->faturacao += (valor * qtd);
    auxil->nCompras++;
}

AuxQ7 criaLista(ComprasDB cdb, int lower, int higher) {
    if (lower < 1) lower = 1;
    if (lower > 12) lower = 12;
    AuxQ7 res = new();
    criaLista(cdb->compras->arvore, lower, higher, res);
    return res;
}

CodigoArray compraTodos(ComprasDB cdb) {
    CodigoArray ca = new();
    compraTodos(cdb->clientes->arvore, ca);
    return ca;
}

struct nodeTop {
    Codigo codigo;
    int totalQtd;
    struct nodeTop *left, *right;
};

TreeTop newNode(Codigo codigo, int totalQtd) {
    TreeTop aux = malloc(sizeof (struct nodeTop));
    aux->codigo = strdup(codigo);
    aux->totalQtd = totalQtd;
    aux->left = NULL;
    aux->right = NULL;
    return aux;
}

void insertNode(TreeTop arvore, Codigo codigo, int totalQtd) {
    if (arvore == NULL) {
        arvore = newNode(codigo, totalQtd);
    } else if (arvore->totalQtd > totalQtd) insertNode(arvore->left, codigo, totalQtd);
    else if (arvore->totalQtd <= totalQtd) insertNode(arvore->right, codigo, totalQtd);
}

TreeTop clienteToTreeTop(Cliente cl) {
    TreeTop aux = NULL;
    CodigoArray ca = new();
    produtosCompradosToTreeTop(cl->prodComprados, aux, ca);
    return aux;
}

static void produtosCompradosToTreeTop(struct simpleProd* sp, TreeTop aux, CodigoArray ca) {
    if (sp != NULL) {
        Codigo codigo = sp->codigo;
        if (in(codigo, ca));
        {
            int qtd = sp->qtdCompradaTotal;
            criaArvore(sp->left, aux, codigo, qtd);
            criaArvore(sp->right, aux, codigo, qtd);
            insert(ca, codigo);
        }
        produtosCompradosToTreeTop(sp->left, aux, ca);
        produtosCompradosToTreeTop(sp->right, aux, ca);
    }
}

static void criaArvore(struct simpleProd* sp, TreeTop aux, Codigo codigo, int qtd) {
    if (sp == NULL) insertNode(aux, codigo, qtd);
    else if (strcmp(sp->codigo, codigo) == 0) qtd += sp->qtdCompradaTotal;
}

CodigoArray topCompras(TreeTop aux) {
    CodigoArray ca = new();
    procTop(aux, ca);
    return ca;
}

static void procTop(TreeTop aux, CodigoArray ca) {
    if (aux != NULL) {
        procTop(aux->right);
        insert(ca, aux->codigo);
        procTop(aux->left);
    }
}

CodigoArray getTopCompras(ComprasDB cdb, Codigo codigo) {
    CodigoArray resol;
    Cliente cl = get(cdb->clientes->arvore, codigo);
    TreeTop res = clienteToTreeTop(cl);
    resol = topCompras(res);
    return resol;
}

CodigoArray getTopComprasMensal(ComprasDB cdb, Codigo codigo, int mes) {
    CodigoArray ca;
    Cliente cl = get(cdb->compras->arvore, codigo,mes);
    TreeTop aux=constroiTopComprasMensal(cl,mes);
    ca=topCompras(aux);
    return ca;
}

TreeTop constroiTopComprasMensal(Cliente cl, int mes) {
    TreeTop tt = NULL;
    constroiTopComprasMensal(tt, cl->prodComprados, mes);
    
}

static void constroiTopComprasMensal(TreeTop tt,struct simpleProd* sp, int mes){
    if(sp!=NULL){
        if(sp->mes==mes) insertNode(tt,sp->codigo,sp->qtdCompradaTotal);
        constroiTopComprasMensal(tt,sp->left,mes);
        constroiTopComprasMensal(tt,sp->right,mes);
    }
}

struct arvoreQ8{
    Codigo codigoC;
    char modo;
    int nrIns;
    struct arvoreQ8 *left, *right;
};

ArvoreClientes new(){
    return NULL;
}

ArvoreClientes newNode(Codigo codigo, char modo){
    ArvoreClientes aux=malloc(sizeof(struct arvoreQ8));
    aux->codigoC=strdup(codigo);
    aux->modo=modo;
    aux->nrIns=1;
    aux->left=aux->right=NULL;
    return aux;
}

void insert(ArvoreClientes ac, Codigo codigo, char modo){
    if(ac==NULL){
        ac=newNode(codigo,modo);
    }
    else if(strcmp(ac->codigoC,codigo)>0) {ac->nrIns++; insert(ac->left,codigo,modo);}
    else if(strcmp(ac->codigoC,codigo)<0) {ac->nrIns++; insert(ac->right,codigo,modo);}
    else if(strcmp(ac->codigoC,codigo)==0){
        if(ac->modo>modo) {ac->nrIns++;insert(ac->left,codigo,modo);}
        else if(ac->modo<modo) {ac->nrIns++;insert(ac->right,codigo,modo);}
    }
}

void dispose(ArvoreClientes ac){
    dispose(ac->left);
    dispose(ac->right);
    free(ac);
}
/*
CodigoArray clientesCompradores(ComprasDB cdb, Codigo codigoP){
    CodigoArray ca=new();
    Produto p=get(cdb->produtos->arvore,codigoP);
    ArvoreClientes ac=produtoToArvoreCl(p);
    constroiClientesArray(ac,ca);
    return ca;
}
*/
ArvoreClientes produtoToArvoreCl(Produto p){
    ArvoreClientes ac=new();
    prodToArvoreCl(p->cliCompradores,ac);
    return ac;
}

static void prodToArvoreCl(struct simpleCli* sc,ArvoreClientes ac){
    if(sc!=NULL){
        if(sc->qtdCompN){
            insert(ac,sc->codigo,'N');
        }
        if(sc->qtdCompP){
            insert(ac,sc->codigo,'P');
        }
        prodToArvoreCl(sc->left,ac);
        prodToArvoreCl(sc->right,ac);
    }
}


int contaClientesDif(ArvoreClientes ac){
    int i=0;
    CodigoArray ca=new();
    contaDiffCli(ac,ca,i);
    return i;
}

static void contaDiffCli(ArvoreClientes ac, CodigoArray ca, int contador){
    if(ac!=NULL){
        if(!in(ac->codigoC,ca)){
            contador++;
            insert(ca,ac->codigoC);
        }
        contaDiffCli(ac->left,ca,contador);
        contaDiffCli(ac->right,ca,contador);
    }
}

struct treeQ12{
    Codigo codigo;
    int qtd;
    struct treeQ12 *left, *right;
};

ArvoreQtd new(){
    return NULL;
}

ArvoreQtd newNode(Codigo codigo, int qtd){
    ArvoreQtd aux=malloc(sizeof(struct treeQ12));
    aux->codigo=strdup(codigo);
    aux->qtd=qtd;
    aux->left=aux->right=NULL;
}

void dispose(ArvoreQtd aq){
    dispose(aq->left);
    dispose(aq->right);
    free(aq);
}

void insert(ArvoreQtd aq, Codigo codigo,int qtd){
    if(aq==NULL){
        aq=newNode(codigo,qtd);
    }
    else if(aq->qtd>qtd) insert(aq->left,codigo,qtd);
    else if(aq->qtd<=qtd) insert(aq->right,codigo,qtd);
}

ArvoreQtd ProdutosToQtdArvore(ComprasDB cdb){
    ArvoreQtd aux=new();
    constroiArvore(cdb->produtos->arvore,aux);
    return aux;
}

CodigoArray getCodigosDecresc(ArvoreQtd aq){
    CodigoArray ca=new();
    getCodigosDecresc(aq,ca);
    return ca;
}

struct parCodQtd{
    Codigo codigo;
    int qtd;
};

ParCodigoQtd new(Codigo codigo, int qtd){
    ParCodigoQtd pcq=malloc(sizeof(struct parCodQtd));
    pcq->codigo=strdup(codigo);
    pcq->qtd=qtd;
    return pcq;
}
Codigo getCodigo(ParCodigoQtd pcq){
    return strdup(pcq->codigo);
}
int getQtd(ParCodigoQtd pcq){
    return pcq->qtd;
}

struct parCodModo{
    Codigo codigo;
    char modo;
};

ParCodigoModo new(Codigo codigo, char modo){
    ParCodigoModo pcm=malloc(sizeof(struct parCodModo));
    pcm->codigo=strdup(codigo);
    pcm->modo=modo;
    return pcm;
}
Codigo getCodigo(ParCodigoModo pcm){
    return strdup(pcm->codigo);
}
char getQtd(ParCodigoModo pcm){
    return pcm->modo;
}