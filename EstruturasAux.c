#include <stdlib.h>
#include <string.h>
#include "EstruturasAux.h"



/*Array de Códigos*/
CodigoArray new(){
    return NULL;
    }
int getSize(CodigoArray ca){
    int i=0;
    while(ca[i]!=NULL)
        i++;
    return i;
}
CodigoArray insert(CodigoArray ca, Codigo co){
    CodigoArray auxil=ca;
    int size=getSize(auxil);
    auxil=(char**)realloc(auxil,(size+1)*strlen(co+1));
    auxil[size]=strdup(co);
    return auxil;
}

void dispose(CodigoArray ca){
    int i=0;
    while(i<getSize(ca))
        free(ca[i]);
    free(ca);
}

int in(Codigo co, CodigoArray ca){
    int flag=0,i;
    for(i=0;i<getSize(ca)&&(!flag);i++)
        if(strcmp(co,ca[i]))flag=1;
    return flag;
}

CodigoArray getFirstN(CodigoArray ca, int n){
    int i;
    int min=min(n,getSize(ca));
    CodigoArray caux=new();
    for(i=0;i<min;i++){
        insert(caux,ca[i]);
    }
    return caux;
}
int min(int x1,int x2){
    if(x1>x2) return x2;
    if(x2>x1) return x1;
    if(x1==x2) return x1;
}

Codigo get(CodigoArray ca, int i){
    return strdup(ca[i]);
}

struct auxR2 {
    int vendasN;
    int vendasP;
    float faturaT;
};

AuxR2 new(int vendasN, int vendasP, float faturaT) {
    AuxR2 auxil = malloc(sizeof (struct auxR2));
    auxil->vendasN = vendasN;
    auxil->vendasP = vendasP;
    auxil->faturaT = faturaT;
    return auxil;
}

int getVendasN(AuxR2 r2) {
    return r2->vendasN;
}

int getVendasP(AuxR2 r2) {
    return r2->vendasP;
}

float getFaturacaoT(AuxR2 r2) {
    return r2->faturaT;
}


static AuxR2 getDadosProduto(Contab c, Codigo codigo, int mes) {
    if (c == NULL) return new(0, 0, 0);
    else if (strcmp(c->codigo,codigo)>0) return getDadosProduto(c->left,codigo,mes);
    else if (strcmp(c->codigo,codigo)<0) return getDadosProduto(c->right,codigo,mes);
    else if (strcmp(c->codigo,codigo)==0) return new((c->vendasN[mes-1]),(c->vendasP[mes-1]),(c->faturaN[mes-1]+c->faturaP[mes-1]));
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

AuxQ7 insereCompra(AuxQ7 auxil, float valor, int qtd) {
    AuxQ7 aux=auxil;
    aux->faturacao += (valor * qtd);
    aux->nCompras++;
    return aux;
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

Table addValor(Table t, int qtd, int mes) {
    Table aux=t;
    if (mes >= 1 && mes <= 12)
        aux->compras[mes - 1] += qtd;
    return aux;
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

TabelaCSV addCliente(TabelaCSV tcsv, int mes) {
    TabelaCSV aux=tcsv;
    aux->clientes[mes - 1]++;
    return aux;
}

TabelaCSV addCompra(TabelaCSV tcsv, int mes){
    TabelaCSV aux=tcsv;
    aux->compra[mes-1]++;
    return aux;
}
void dispose(TabelaCSV tcsv) {
    free(tcsv->clientes);
    free(tcsv->compras);
    free(tcsv);
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

Par addCliente(Par p) {
    Par aux=p;
    aux->clientesSemCompras++;
    return aux;
}

Par addProduto(Par p) {
    Par aux=p;
    aux->produtosNaoComprados++;
    return aux;
}

int getClientesSemCompras(Par p) {
    return p->clientesSemCompras;
}

int getProdutosNaoComprados(Par p) {
    return p->produtosNaoComprados;
}


int in(int x, int linf, int lsup) {
    return (x = >linf && x <= lsup);
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

TreeTop insertNode(TreeTop arvore, Codigo codigo, int totalQtd) {
    TreeTop aux=arvore;
    if (aux == NULL) {
        aux = newNode(codigo, totalQtd);
    } else if (aux->totalQtd > totalQtd) aux->left=insertNode(aux->left, codigo, totalQtd);
    else if (aux->totalQtd <= totalQtd) aux->right=insertNode(aux->right, codigo, totalQtd);
    return aux;
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

ArvoreClientes insert(ArvoreClientes ac, Codigo codigo, char modo){
    ArvoreClientes aux=ac;
    if(aux==NULL){
        aux=newNode(codigo,modo);
    }
    else if(strcmp(aux->codigoC,codigo)>0) {aux->nrIns++; aux->left=insert(aux->left,codigo,modo);}
    else if(strcmp(aux->codigoC,codigo)<0) {aux->nrIns++; aux->right=insert(aux->right,codigo,modo);}
    else if(strcmp(aux->codigoC,codigo)==0){
        if(aux->modo>modo) {aux->nrIns++;aux->left=insert(aux->left,codigo,modo);}
        else if(aux->modo<modo) {aux->nrIns++;aux->right=insert(aux->right,codigo,modo);}
    }
}

void dispose(ArvoreClientes ac){
    dispose(ac->left);
    dispose(ac->right);
    free(ac);
}

int contaClientesDif(ArvoreClientes ac){
    int i;
    CodigoArray ca=new();
    i=contaDiffCli(ac,ca);
    return i;
}

static int contaDiffCli(ArvoreClientes ac, CodigoArray ca){
    int i=0;
    if(ac!=NULL){
        i=contaDiffCli(ac->left,ca);
        i=contaDiffCli(ac->right,ca);
        if(!in(ac->codigoC,ca)){
            i++;
            insert(ca,ac->codigoC);
        }
        
    }
    return i;
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

ArvoreQtd insert(ArvoreQtd aq, Codigo codigo,int qtd){
    ArvoreQtd aux=aq;
    if(aux==NULL){
        aux=newNode(codigo,qtd);
    }
    else if(aux->qtd>qtd) aux->left=insert(aux->left,codigo,qtd);
    else if(aux->qtd<=qtd) aux->right=insert(aux->right,codigo,qtd);
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

void dispose(ParCodigoQtd pcq){
    free(pcq);
}

ListaDePCQ new(){
    return NULL;
}
int getSize(ListaDePCQ lpcq){
    int i;
    for(i=0;lpcq[i]!=NULL;i++);
    return i;
}
ListaDePCQ insert(ListaDePCQ lpcq, Codigo codigo,char modo){
    ListaDePCQ aux=lpcq;
    int size=getSize(aux);
    ParCodigoQtd pcq=new(codigo,modo);
    aux=realloc(aux,(size+1)*sizeof(struct parCodModo));
    aux[size]=pcq;
    return aux;
}

ParCodigoQtd get(ListaDePCQ lpcq, int pos){
    if(pos>getSize(lpcq)) return NULL;
    return lpcq[pos];
}

void dispose(ListaDePCQ lpcq){
    int i;
    for(i=0;i<getSize(lpcq);i++)
        dispose(lpcq[i]);
    dispose(lpcq);
}

ListaDePCQ getFirstN(ListaDePCQ lpcq,int n){
    int i;
    ListaDePCQ auxil=new();
    for(i=0;i<n&&i<getSize(lpcq);i++)
        auxil[i]=lpcq[i];
    return auxil;
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
char getModo(ParCodigoModo pcm){
    return pcm->modo;
}

void dispose(ParCodigoModo pcm){
    free(pcm);
}
ListaDePCM new(){
    return NULL;
}
int getSize(ListaDePCM lpcm){
    int i;
    for(i=0;lpcm[i]!=NULL;i++);
    return i;
}
ListaDePCM insert(ListaDePCM lpcm, Codigo codigo,char modo){
    ListaDePCM aux=lpcm;
    int size=getSize(aux);
    ParCodigoModo pcm=new(codigo,modo);
    aux=realloc(aux,(size+1)*sizeof(struct parCodModo));
    aux[size]=pcm;
    return aux;
}

ParCodigoModo get(ListaDePCM lpcm, int pos){
    if(pos>getSize(lpcm)) return NULL;
    return lpcm[pos];
}

void dispose(ListaDePCM lpcm){
    int i;
    for(i=0;i<getSize(lpcm);i++)
        dispose(lpcm[i]);
    dispose(lpcm);
}

ListaDePCM getFirstN(ListaDePCM lpcm,int n){
    int i;
    ListaDePCM aux=new();
    for(i=0;i<n&&i<getSize(lpcm);i++)
        aux[i]=lpcm[i];
    return aux;
    
}