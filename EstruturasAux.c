#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "EstruturasAux.h"

/*Array de Códigos*/
CodigoArray new() {
    return NULL;
}

int getSize(CodigoArray ca) {
    int i = 0;
    while (ca[i] != NULL)
        i++;
    return i;
}

CodigoArray insert(CodigoArray ca, Codigo co) {
    CodigoArray auxil = ca;
    int size; 
    if (auxil == NULL) {
        auxil=(char**)malloc(1*strlen(co+1));
        auxil[0]=strdup(co);
    } else {
        size= getSize(auxil);
        auxil = (char**) realloc(auxil, (size + 1) * strlen(co + 1));
        auxil[size] = strdup(co);
        
    }
    return auxil;
}

void dispose(CodigoArray ca) {
    int i = 0;
    while (i < getSize(ca))
        free(ca[i]);
    free(ca);
}

int in(Codigo co, CodigoArray ca) {
    int flag = 0, i;
    for (i = 0; i < getSize(ca)&&(!flag); i++)
        if (strcmp(co, ca[i]))flag = 1;
    return flag;
}

CodigoArray getFirstN(CodigoArray ca, int n) {
    int i;
    int min = min(n, getSize(ca));
    CodigoArray caux = new();
    for (i = 0; i < min; i++) {
        insert(caux, ca[i]);
    }
    return caux;
}

int min(int x1, int x2) {
    if (x1 > x2) return x2;
    if (x2 > x1) return x1;
    if (x1 == x2) return x1;
}

Codigo get(CodigoArray ca, int i) {
    return strdup(ca[i]);
}

/**Contabilidade*/
struct auxR2 {
    int vendasN;
    int vendasP;
    float faturaT;
};

VendasProduto new(int vendasN, int vendasP, float faturaT) {
    VendasProduto auxil = malloc(sizeof (struct auxR2));
    auxil->vendasN = vendasN;
    auxil->vendasP = vendasP;
    auxil->faturaT = faturaT;
    return auxil;
}

int getVendasN(VendasProduto r2) {
    return r2->vendasN;
}

int getVendasP(VendasProduto r2) {
    return r2->vendasP;
}

float getFaturacaoT(VendasProduto r2) {
    return r2->faturaT;
}

struct auxilQ7 {
    int nCompras;
    float faturacao;
};

Faturacao new() {
    Faturacao aux = malloc(sizeof (struct auxilQ7));
    aux->faturacao = 0.0;
    aux->nCompras = 0;
    return aux;
}

void dispose(Faturacao aux) {
    free(aux);
}

float getFaturacao(Faturacao aux) {
    return aux->faturacao;
}

int getNCompras(Faturacao aux) {
    return aux->nCompras;
}

Faturacao insereCompra(Faturacao auxil, float valor, int qtd) {
    Faturacao aux = auxil;
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
    Table aux = t;
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

/**CSV*/
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
    TabelaCSV aux = tcsv;
    aux->clientes[mes - 1]++;
    return aux;
}

TabelaCSV addCompra(TabelaCSV tcsv, int mes) {
    TabelaCSV aux = tcsv;
    aux->compra[mes - 1]++;
    return aux;
}

TabelaCSV addCompras(TabelaCSV tcsv, int mes, int vezes) {
    TabelaCSV aux = tcsv;
    aux->compra[mes - 1] += vezes;
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
    Par aux = p;
    aux->clientesSemCompras++;
    return aux;
}

Par addProduto(Par p) {
    Par aux = p;
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
    TreeTop aux = arvore;
    if (aux == NULL) {
        aux = newNode(codigo, totalQtd);
    } else if (aux->totalQtd > totalQtd) aux->left = insertNode(aux->left, codigo, totalQtd);
    else if (aux->totalQtd <= totalQtd) aux->right = insertNode(aux->right, codigo, totalQtd);
    return aux;
}

CodigoArray maisComprados(TreeTop tt, CodigoArray ca) {
    CodigoArray aux = ca;
    if (tt) {
        aux = maisComprados(tt->right, aux);
        aux = insert(aux, tt->codigo);
        aux = maisComprados(tt->left, aux);
    } else return aux;
}

struct arvoreQ8 {
    Codigo codigoC;
    char modo;
    int nrIns;
    struct arvoreQ8 *left, *right;
};

ArvoreClientes new() {
    return NULL;
}

ArvoreClientes newNode(Codigo codigo, char modo) {
    ArvoreClientes aux = malloc(sizeof (struct arvoreQ8));
    aux->codigoC = strdup(codigo);
    aux->modo = modo;
    aux->nrIns = 1;
    aux->left = aux->right = NULL;
    return aux;
}

ArvoreClientes insert(ArvoreClientes ac, Codigo codigo, char modo) {
    ArvoreClientes aux = ac;
    if (aux == NULL) {
        aux = newNode(codigo, modo);
    } else if (strcmp(aux->codigoC, codigo) > 0) {
        aux->nrIns++;
        aux->left = insert(aux->left, codigo, modo);
    } else if (strcmp(aux->codigoC, codigo) < 0) {
        aux->nrIns++;
        aux->right = insert(aux->right, codigo, modo);
    } else if (strcmp(aux->codigoC, codigo) == 0) {
        if (aux->modo > modo) {
            aux->nrIns++;
            aux->left = insert(aux->left, codigo, modo);
        } else if (aux->modo < modo) {
            aux->nrIns++;
            aux->right = insert(aux->right, codigo, modo);
        }
    }
}

void dispose(ArvoreClientes ac) {
    dispose(ac->left);
    dispose(ac->right);
    free(ac);
}

int contaClientesDif(ArvoreClientes ac) {
    int i;
    CodigoArray ca = new();
    i = contaDiffCli(ac, ca);
    return i;
}

static int contaDiffCli(ArvoreClientes ac, CodigoArray ca) {
    int i = 0;
    if (ac != NULL) {
        i = contaDiffCli(ac->left, ca);
        i = contaDiffCli(ac->right, ca);
        if (!in(ac->codigoC, ca)) {
            i++;
            insert(ca, ac->codigoC);
        }

    }
    return i;
}

struct treeQ12 {
    Codigo codigo;
    int qtd;
    struct treeQ12 *left, *right;
};

ArvoreQtd new() {
    return NULL;
}

ArvoreQtd newNode(Codigo codigo, int qtd) {
    ArvoreQtd aux = malloc(sizeof (struct treeQ12));
    aux->codigo = strdup(codigo);
    aux->qtd = qtd;
    aux->left = aux->right = NULL;
}

void dispose(ArvoreQtd aq) {
    dispose(aq->left);
    dispose(aq->right);
    free(aq);
}

ArvoreQtd insert(ArvoreQtd aq, Codigo codigo, int qtd) {
    ArvoreQtd aux = aq;
    if (aux == NULL) {
        aux = newNode(codigo, qtd);
    } else if (aux->qtd > qtd) aux->left = insert(aux->left, codigo, qtd);
    else if (aux->qtd <= qtd) aux->right = insert(aux->right, codigo, qtd);
}

struct parCodQtd {
    Codigo codigo;
    int qtd;
};

ParCodigoQtd new(Codigo codigo, int qtd) {
    ParCodigoQtd pcq = malloc(sizeof (struct parCodQtd));
    pcq->codigo = strdup(codigo);
    pcq->qtd = qtd;
    return pcq;
}

Codigo getCodigo(ParCodigoQtd pcq) {
    return strdup(pcq->codigo);
}

int getQtd(ParCodigoQtd pcq) {
    return pcq->qtd;
}

void dispose(ParCodigoQtd pcq) {
    free(pcq);
}

ListaDePCQ new() {
    return NULL;
}

int getSize(ListaDePCQ lpcq) {
    int i;
    for (i = 0; lpcq[i] != NULL; i++);
    return i;
}

ListaDePCQ insert(ListaDePCQ lpcq, Codigo codigo, int qtd) {
    ListaDePCQ aux = lpcq;
    int size = getSize(aux);
    ParCodigoQtd pcq = new(codigo, qtd);
    aux = realloc(aux, (size + 1) * sizeof (struct parCodModo));
    aux[size] = pcq;
    return aux;
}

ParCodigoQtd get(ListaDePCQ lpcq, int pos) {
    if (pos > getSize(lpcq)) return NULL;
    return lpcq[pos];
}

void dispose(ListaDePCQ lpcq) {
    int i;
    for (i = 0; i < getSize(lpcq); i++)
        dispose(lpcq[i]);
    dispose(lpcq);
}

ListaDePCQ getFirstN(ListaDePCQ lpcq, int n) {
    int i;
    ListaDePCQ auxil = new();
    for (i = 0; i < n && i < getSize(lpcq); i++)
        auxil[i] = lpcq[i];
    return auxil;
}

struct parCodModo {
    Codigo codigo;
    char modo;
};

ParCodigoModo new(Codigo codigo, char modo) {
    ParCodigoModo pcm = malloc(sizeof (struct parCodModo));
    pcm->codigo = strdup(codigo);
    pcm->modo = modo;
    return pcm;
}

Codigo getCodigo(ParCodigoModo pcm) {
    return strdup(pcm->codigo);
}

char getModo(ParCodigoModo pcm) {
    return pcm->modo;
}

void dispose(ParCodigoModo pcm) {
    free(pcm);
}

ListaDePCM new() {
    return NULL;
}

int getSize(ListaDePCM lpcm) {
    int i;
    for (i = 0; lpcm[i] != NULL; i++);
    return i;
}

ListaDePCM insert(ListaDePCM lpcm, Codigo codigo, char modo) {
    ListaDePCM aux = lpcm;
    int size = getSize(aux);
    ParCodigoModo pcm = new(codigo, modo);
    aux = realloc(aux, (size + 1) * sizeof (struct parCodModo));
    aux[size] = pcm;
    return aux;
}

ParCodigoModo get(ListaDePCM lpcm, int pos) {
    if (pos > getSize(lpcm)) return NULL;
    return lpcm[pos];
}

void dispose(ListaDePCM lpcm) {
    int i;
    for (i = 0; i < getSize(lpcm); i++)
        dispose(lpcm[i]);
    dispose(lpcm);
}

ListaDePCM getFirstN(ListaDePCM lpcm, int n) {
    int i;
    ListaDePCM aux = new();
    for (i = 0; i < n && i < getSize(lpcm); i++)
        aux[i] = lpcm[i];
    return aux;

}

ListaDePCM travessiaArvore(ArvoreClientes ac, ListaDePCM l) {
    ListaDePCM aux = l;
    if (ac) {
        aux = insert(aux, ac->codigoC, ac->modo);
        aux = travessiaArvore(ac->left, aux);
        aux = travessiaArvore(ac->right, aux);
    } else return aux;
}

ListaDePCQ travessiaDecrescente(ArvoreQtd aq, ListaDePCQ l) {
    ListaDePCQ aux = l;
    if (aq) {
        aux = travessiaDecrescente(aq->right, l);
        aux = insert(aux, aq->codigo, aux->qtd);
        aux = travessiaDecrescente(aq->left, l);
    } else return aux;
}

CodigoArray getCodigosDecresc(ArvoreQtd aq, CodigoArray ca) {
    CodigoArray aux = ca;
    if (aq) {
        aux = getCodigosDecresc(aq->right, aux);
        aux = insert(aux, aq->codigo);
        aux = getCodigosDecresc(aq->left, aux);
    } else return aux;
}

CodigoArray travessiaDecrescente(TreeTop tt, CodigoArray ca) {
    CodigoArray aux = ca;
    if (tt) {
        aux = travessiaDecrescente(tt->right);
        aux = insert(aux, tt->codigo);
        aux = travessiaDecrescente(tt->left);
    } else return aux;
}

TreeTop update(TreeTop tt, Codigo codigo, int qtdTotal) {
    TreeTop aux = tt;
    if (aux) {
        if (strcmp(aux->codigo, codigo) > 0) aux = update(tt->left, codigo, qtdTotal);
        else if (strcmp(aux->codigo, codigo) < 0) aux = update(tt->right, codigo, qtdTotal);
        else if (strcmp(aux->codigo, codigo) == 0) {
            aux->totalQtd += qtdTotal;
            return aux;
        }
    } else return aux;
}