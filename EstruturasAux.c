#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "EstruturasAux.h"
#include "CusTypes.h"

/*Array de Códigos*/
CodigoArray newCA() {
    return NULL;
}

int CA_getSize(CodigoArray ca) {
    int i = 0;
    while (ca[i] != NULL)
        i++;
    return i;
}

CodigoArray CA_insert(CodigoArray ca, Codigo co) {
    CodigoArray auxil = ca;
    int size;
    if (auxil == NULL) {
        auxil = (char**) malloc(1 * strlen(co + 1));
        auxil[0] = strdup(co);
    } else {
        size = CA_getSize(auxil);
        auxil = (char**) realloc(auxil, (size + 1) * strlen(co + 1));
        auxil[size] = strdup(co);

    }
    return auxil;
}

void CA_dispose(CodigoArray ca) {
    int i = 0;
    while (i < CA_getSize(ca))
        free(ca[i]);
    free(ca);
}

int CA_in(Codigo co, CodigoArray ca) {
    int flag = 0, i;
    for (i = 0; i < CA_getSize(ca)&&(!flag); i++)
        if (strcmp(co, ca[i]))flag = 1;
    return flag;
}

CodigoArray CA_getFirstN(CodigoArray ca, int n) {
    int i;
    int minim = min(n, CA_getSize(ca));
    CodigoArray caux = newCA();
    for (i = 0; i < minim; i++) {
        CA_insert(caux, ca[i]);
    }
    return caux;
}

Codigo CA_get(CodigoArray ca, int i) {
	    if(ca)
	return strdup(ca[min(i,CA_getSize(ca))]);
	else return ca[CA_getSize(ca)];
	return ca[CA_getSize(ca)];
}

/**Contabilidade*/
struct auxR2 {
    int vendasN;
    int vendasP;
    float faturaT;
};

VendasProduto newVP(int vendasN, int vendasP, float faturaT) {
    VendasProduto auxil = malloc(sizeof (struct auxR2));
    auxil->vendasN = vendasN;
    auxil->vendasP = vendasP;
    auxil->faturaT = faturaT;
    return auxil;
}

int VP_getVendasN(VendasProduto r2) {
    return r2->vendasN;
}

int VP_getVendasP(VendasProduto r2) {
    return r2->vendasP;
}

float VP_getFaturacaoT(VendasProduto r2) {
    return r2->faturaT;
}

void VP_dispose(VendasProduto r2) {
    free(r2);
}

struct auxilQ7 {
    int nCompras;
    float faturacao;
};


Faturacao newFat() {
    Faturacao aux = malloc(sizeof (struct auxilQ7));
    aux->faturacao = 0.0;
    aux->nCompras = 0;
    return aux;
}

void Fat_dispose(Faturacao aux) {
    free(aux);
}

float Fat_getFaturacao(Faturacao aux) {
    return aux->faturacao;
}

int Fat_getNCompras(Faturacao aux) {
    return aux->nCompras;
}

Faturacao Fat_insereCompra(Faturacao auxil, float valor, int qtd) {
    Faturacao aux = auxil;
    aux->faturacao += (valor * qtd);
    aux->nCompras++;
    return aux;
}

struct tabela {
    Codigo codigo;
    int compras[12];
};

Table newTab(Codigo codigo) {
    int i;
    Table aux = malloc(sizeof (struct tabela));
    aux->codigo = strdup(codigo);
    for (i = 0; i < 12; i++)
        aux->compras[i] = 0;
    return aux;
}

Table Tab_addValor(Table t, int qtd, int mes) {
    Table aux = t;
    if (mes >= 1 && mes <= 12)
        aux->compras[mes - 1] += qtd;
    return aux;
}

Codigo Tab_getCodigo(Table t) {
    return strdup(t->codigo);
}

int Tab_getCompras(Table t, int mes) {
    return t->compras[mes - 1];
}

void Tab_dispose(Table t) {
    free(t->codigo);
    free(t->compras);
    free(t);
}

void Tab_toTxtFile(Table t, char* filename) {
    int i;
    FILE* file = fopen(filename, "w");
    if (file) {
        fprintf(file, "Codigo: %s\n", t->codigo);
        for (i = 0; i < 12; i++)
            fprintf(file, "Realizou %d compras no mes %d\n", t->compras[i], i + 1);
        fclose(file);
    } else printf("Não foi possível criar o ficheiro\n");
}

/**CSV*/
struct tableQ11 {
    int compras[12];
    int clientes[12];
};

TabelaCSV newCSV() {
    TabelaCSV aux = malloc(sizeof (struct tableQ11));
    int i;
    for (i = 0; i < 12; i++) {
        aux->compras[i] = 0;
        aux->clientes[i] = 0;
    }
    return aux;
}

TabelaCSV CSV_addCliente(TabelaCSV tcsv, int mes) {
    TabelaCSV aux = tcsv;
    aux->clientes[mes - 1]++;
    return aux;
}

TabelaCSV CSV_addCompra(TabelaCSV tcsv, int mes) {
    TabelaCSV aux = tcsv;
    aux->compras[mes - 1]++;
    return aux;
}

TabelaCSV CSV_addCompras(TabelaCSV tcsv, int mes, int vezes) {
    TabelaCSV aux = tcsv;
    aux->compras[mes - 1] += vezes;
    return aux;
}

void CSV_dispose(TabelaCSV tcsv) {
    free(tcsv->clientes);
    free(tcsv->compras);
    free(tcsv);
}

void CSV_toCsvFile(TabelaCSV csv, char* filename) {
    int i;
    FILE *file = fopen(strcat(filename, ".csv"), "w");
    if (file) {
        fprintf(file, "\"Mês\",\"Compras\",\"Clientes\"\n");
        for (i = 0; i < 12; i++) {
            fprintf(file, "\"%d\",\"%d\",\"%d\"\n", i + 1, csv->compras[i], csv->clientes[i]);
        }
        fclose(file);
    } else printf("Não foi possível criar o ficheiro\n");
}

struct par {
    int clientesSemCompras;
    int produtosNaoComprados;
};

Par newPar() {
    Par aux = malloc(sizeof (struct par));
    aux->clientesSemCompras = 0;
    aux->produtosNaoComprados = 0;
    return aux;
}

void Par_dispose(Par p) {
    free(p);
}

Par Par_addCliente(Par p) {
    Par aux = p;
    aux->clientesSemCompras++;
    return aux;
}

Par Par_addProduto(Par p) {
    Par aux = p;
    aux->produtosNaoComprados++;
    return aux;
}

int Par_getClientesSemCompras(Par p) {
    return p->clientesSemCompras;
}

int Par_getProdutosNaoComprados(Par p) {
    return p->produtosNaoComprados;
}

struct nodeTop {
    Codigo codigo;
    int totalQtd;
    struct nodeTop *left, *right;
};

TreeTop newTT() {
    return NULL;
}

TreeTop TT_newNode(Codigo codigo, int totalQtd) {
    TreeTop aux = malloc(sizeof (struct nodeTop));
    aux->codigo = strdup(codigo);
    aux->totalQtd = totalQtd;
    aux->left = NULL;
    aux->right = NULL;
    return aux;
}

TreeTop TT_insertNode(TreeTop arvore, Codigo codigo, int totalQtd) {
    TreeTop aux = arvore;
    if (aux == NULL) {
        aux = TT_newNode(codigo, totalQtd);
    } else if (aux->totalQtd > totalQtd) aux->left = TT_insertNode(aux->left, codigo, totalQtd);
    else if (aux->totalQtd <= totalQtd) aux->right = TT_insertNode(aux->right, codigo, totalQtd);
    return aux;
}

CodigoArray TT_maisComprados(TreeTop tt, CodigoArray ca) {
    CodigoArray aux = ca;
    if (tt) {
        aux = TT_maisComprados(tt->right, aux);
        aux = CA_insert(aux, tt->codigo);
        aux = TT_maisComprados(tt->left, aux);
    } else return aux;
    return aux;
}

void TT_dispose(TreeTop tt) {
    TT_dispose(tt->left);
    TT_dispose(tt->right);
    free(tt);
}

struct arvoreQ8 {
    Codigo codigoC;
    char modo;
    int nrIns;
    struct arvoreQ8 *left, *right;
};

ArvoreClientes newAC() {
    return NULL;
}

ArvoreClientes AC_newNode(Codigo codigo, char modo) {
    ArvoreClientes aux = malloc(sizeof (struct arvoreQ8));
    aux->codigoC = strdup(codigo);
    aux->modo = modo;
    aux->nrIns = 1;
    aux->left = aux->right = NULL;
    return aux;
}

ArvoreClientes AC_insert(ArvoreClientes ac, Codigo codigo, char modo) {
    ArvoreClientes aux = ac;
    if (aux == NULL) {
        aux = AC_newNode(codigo, modo);
    } else if (strcmp(aux->codigoC, codigo) > 0) {
        aux->nrIns++;
        aux->left = AC_insert(aux->left, codigo, modo);
    } else if (strcmp(aux->codigoC, codigo) < 0) {
        aux->nrIns++;
        aux->right = AC_insert(aux->right, codigo, modo);
    } else if (strcmp(aux->codigoC, codigo) == 0) {
        if (aux->modo > modo) {
            aux->nrIns++;
            aux->left = AC_insert(aux->left, codigo, modo);
        } else if (aux->modo < modo) {
            aux->nrIns++;
            aux->right = AC_insert(aux->right, codigo, modo);
        }
    }
    return aux;
}

void AC_dispose(ArvoreClientes ac) {
    AC_dispose(ac->left);
    AC_dispose(ac->right);
    free(ac);
}

int AC_contaClientesDif(ArvoreClientes ac) {
    int i;
    CodigoArray ca = newCA();
    i = AC_contaDiffCli(ac, ca);
    return i;
}

int AC_contaDiffCli(ArvoreClientes ac, CodigoArray ca) {
    int i = 0;
    if (ac != NULL) {
        i = AC_contaDiffCli(ac->left, ca);
        i = AC_contaDiffCli(ac->right, ca);
        if (!CA_in(ac->codigoC, ca)) {
            i++;
            CA_insert(ca, ac->codigoC);
        }

    }
    return i;
}

struct treeQ12 {
    Codigo codigo;
    int qtd;
    struct treeQ12 *left, *right;
};

ArvoreQtd newAQ() {
    return NULL;
}

ArvoreQtd AQ_newNode(Codigo codigo, int qtd) {
    ArvoreQtd aux = malloc(sizeof (struct treeQ12));
    aux->codigo = strdup(codigo);
    aux->qtd = qtd;
    aux->left = aux->right = NULL;
    return aux;
}

void AQ_dispose(ArvoreQtd aq) {
    AQ_dispose(aq->left);
    AQ_dispose(aq->right);
    free(aq);
}

ArvoreQtd AQ_insert(ArvoreQtd aq, Codigo codigo, int qtd) {
    ArvoreQtd aux = aq;
    if (aux == NULL) {
        aux = AQ_newNode(codigo, qtd);
    } else if (aux->qtd > qtd) aux->left = AQ_insert(aux->left, codigo, qtd);
    else if (aux->qtd <= qtd) aux->right = AQ_insert(aux->right, codigo, qtd);
    return aux;
}

struct parCodQtd {
    Codigo codigo;
    int qtd;
};

ParCodigoQtd newPCQ(Codigo codigo, int qtd) {
    ParCodigoQtd pcq = malloc(sizeof (struct parCodQtd));
    pcq->codigo = strdup(codigo);
    pcq->qtd = qtd;
    return pcq;
}

Codigo PCQ_getCodigo(ParCodigoQtd pcq) {
    return strdup(pcq->codigo);
}

int PCQ_getQtd(ParCodigoQtd pcq) {
    return pcq->qtd;
}

void PCQ_dispose(ParCodigoQtd pcq) {
    free(pcq);
}

ListaDePCQ newLPCQ() {
    return NULL;
}

int LPCQ_getSize(ListaDePCQ lpcq) {
    return sizeof (lpcq) / sizeof (struct parCodQtd);
}

ListaDePCQ LPCQ_insert(ListaDePCQ lpcq, Codigo codigo, int qtd) {
    ListaDePCQ aux = lpcq;
    int size = LPCQ_getSize(aux);
    ParCodigoQtd pcq = newPCQ(codigo, qtd);
    if (aux == NULL) {
        aux = malloc(sizeof (struct parCodQtd));
        aux[0] = pcq;
    } else {
        aux = realloc(aux, (size + 1) * sizeof (struct parCodQtd));
        aux[size] = pcq;
    }

    return aux;
}

ParCodigoQtd LPCQ_get(ListaDePCQ lpcq, int pos) {
    if (pos > LPCQ_getSize(lpcq)) return NULL;
    else return lpcq[pos];

}

void LPCQ_dispose(ListaDePCQ lpcq) {
    int i;
    for (i = 0; i < LPCQ_getSize(lpcq); i++)
        PCQ_dispose(LPCQ_get(lpcq, i));
    free(lpcq);
}

ListaDePCQ LPCQ_getFirstN(ListaDePCQ lpcq, int n) {
    int i;
    ListaDePCQ auxil = newLPCQ();
    for (i = 0; i < n && i < LPCQ_getSize(lpcq); i++)
        auxil[i] = lpcq[i];
    return auxil;
}

struct parCodModo {
    Codigo codigo;
    char modo;
};

ParCodigoModo newPCM(Codigo codigo, char modo) {
    ParCodigoModo pcm = malloc(sizeof (struct parCodModo));
    pcm->codigo = strdup(codigo);
    pcm->modo = modo;
    return pcm;
}

Codigo PCM_getCodigo(ParCodigoModo pcm) {
    return strdup(pcm->codigo);
}

char PCM_getModo(ParCodigoModo pcm) {
    return pcm->modo;
}

void PCM_dispose(ParCodigoModo pcm) {
    free(pcm);
}

ListaDePCM newLPCM() {
    return NULL;
}

int LPCM_getSize(ListaDePCM lpcm) {
    return sizeof (lpcm) / sizeof (struct parCodModo);
}

ListaDePCM LPCM_insert(ListaDePCM lpcm, Codigo codigo, char modo) {
    ListaDePCM aux = lpcm;
    int size = LPCM_getSize(aux);
    ParCodigoModo pcm = newPCM(codigo, modo);
    if (aux == NULL) {
        aux = malloc(sizeof (struct parCodModo));
        aux[0] = pcm;
    } else {
        aux = realloc(aux, (size + 1) * sizeof (struct parCodModo));
        aux[size] = pcm;

    }
    return aux;
}

ParCodigoModo LPCM_get(ListaDePCM lpcm, int pos) {
    if (pos > LPCM_getSize(lpcm)) return NULL;
    return lpcm[pos];
}

void LPCM_dispose(ListaDePCM lpcm) {
    int i;
    for (i = 0; i < LPCM_getSize(lpcm); i++)
        PCM_dispose(LPCM_get(lpcm, i));
    free(lpcm);
}

ListaDePCM LPCM_getFirstN(ListaDePCM lpcm, int n) {
    int i;
    ListaDePCM aux = newLPCM();
    for (i = 0; i < n && i < LPCM_getSize(lpcm); i++)
        aux[i] = lpcm[i];
    return aux;

}

ListaDePCM AC_travessiaArvore(ArvoreClientes ac, ListaDePCM l) {
    ListaDePCM aux = l;
    if (ac) {
        aux = LPCM_insert(aux, ac->codigoC, ac->modo);
        aux = AC_travessiaArvore(ac->left, aux);
        aux = AC_travessiaArvore(ac->right, aux);
    } else return aux;
    return aux;
}

ListaDePCQ AQ_travessiaDecrescente(ArvoreQtd aq, ListaDePCQ l) {
    ListaDePCQ aux = l;
    if (aq) {
        aux = AQ_travessiaDecrescente(aq->right, l);
        aux = LPCQ_insert(aux, aq->codigo, aq->qtd);
        aux = AQ_travessiaDecrescente(aq->left, l);
    } else return aux;
    return aux;
}

CodigoArray AQ_getCodigosDecresc(ArvoreQtd aq, CodigoArray ca) {
    CodigoArray aux = ca;
    if (aq) {
        aux = AQ_getCodigosDecresc(aq->right, aux);
        aux = CA_insert(aux, aq->codigo);
        aux = AQ_getCodigosDecresc(aq->left, aux);
    } else return aux;
    return aux;
}

CodigoArray TT_travessiaDecrescente(TreeTop tt, CodigoArray ca) {
    CodigoArray aux = ca;
    if (tt) {
        aux = TT_travessiaDecrescente(tt->right, aux);
        aux = CA_insert(aux, tt->codigo);
        aux = TT_travessiaDecrescente(tt->left, aux);
    } else return aux;
    return aux;
}

TreeTop TT_update(TreeTop tt, Codigo codigo, int qtdTotal) {
    TreeTop aux = tt;
    if (aux) {
        if (strcmp(aux->codigo, codigo) > 0) aux = TT_update(tt->left, codigo, qtdTotal);
        else if (strcmp(aux->codigo, codigo) < 0) aux = TT_update(tt->right, codigo, qtdTotal);
        else if (strcmp(aux->codigo, codigo) == 0) {
            aux->totalQtd += qtdTotal;
            return aux;
        }
    } else return aux;
    return aux;
}
