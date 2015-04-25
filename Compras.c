
#include "Compras.h"
#include "EstruturasAux.h"
#include <stdlib.h>
#include <string.h>
#include "CusTypes.h"

struct compra {
    Codigo codigoP;
    float valorUni;
    int quantidade;
    char modo;
    Codigo codigoC;
    int mes;
    struct compra *left, *right;
};

struct cliente {
    Codigo codigo;
    int compraMes[12];
    struct simpleProd* prodComprados;
    int nCompras;
    struct cliente *left, *right;

};

struct produto {
    Codigo codigo;
    struct simpleCli* cliCompradores;
    int nVezesComprado;
    int qtdComprada;
    int compradoMes[12];
    struct produto *left, *right;
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

struct simpleProd* newSP(Codigo codigo, int mes) {
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
    struct simpleCli *left, *right;
};

struct simpleCli* newSC(Codigo codigo, int mes) {
    struct simpleCli* aux = malloc(sizeof (struct simpleCli));
    aux->codigo = strdup(codigo);
    aux->qtdCompradaTotal = aux->qtdCompN = aux->qtdCompP = 0;
    aux->valorN = aux->valorP = aux->valorTotal = 0;
    aux->mes = mes;
    aux->left = aux->right = NULL;
    return aux;
}



struct comprasDB {
    Compra compras;
    Cliente clientes;
    Produto produtos;
};



Compra newComp(Codigo codigoP, float valorUni, int quantidade, char modo, Codigo codigoC, int mes) {
    Compra aux = malloc(sizeof (struct compra));
    aux->codigoP = strdup(codigoP);
    aux->valorUni = valorUni;
    aux->quantidade = quantidade;
    aux->modo = modo;
    aux->codigoC = strdup(codigoC);
    aux->mes = mes;
    aux->left=aux->right=NULL;
    return aux;
}

Codigo Comp_getCodigoP(Compra com) {
    return strdup(com->codigoP);
}

float Comp_getValorUni(Compra com) {
    return com->valorUni;
}

int Comp_getQuantidade(Compra com) {
    return com->quantidade;
}

char Comp_getModo(Compra com) {
    return com->modo;
}

Codigo Comp_getCodigoC(Compra com) {
    return strdup(com->codigoC);
}

int Comp_getMes(Compra com) {
    return com->mes;
}

int Comp_equals(Compra c1, Compra c2) {
    int ch1, ch2, ch3, ch4, ch5, ch6;
    ch1 = strcmp(c1->codigoP, c2->codigoP);
    ch2 = c1->valorUni - c2->valorUni;
    ch3 = c1->quantidade - c2->quantidade;
    ch4 = c1->modo - c2->modo;
    ch5 = strcmp(c1->codigoC, c2->codigoC);
    ch6 = c1->mes - c2->mes;
    return !(ch1 || ch2 || ch3 || ch4 || ch5 || ch6);
}



Compra newCompT() {
    return NULL;
}

Cliente newClienT() {
    return NULL;
}

Produto newProdT() {
    return NULL;
}

Compra CompT_insert(Compra ct, Codigo codigoP, float valorUni, int quantidade, char modo, Codigo codigoC, int mes) {
    Compra aux = ct;
    if(!aux){
	aux=newComp(codigoP,valorUni,quantidade,modo,codigoC,mes);
}
    else if(strcmp(aux->codigoP,codigoP)>0) aux->left=CompT_insert(aux->left,codigoP,valorUni,quantidade,modo,codigoC,mes);
    else if(strcmp(aux->codigoP,codigoP)<=0) aux->right=CompT_insert(aux->right,codigoP,valorUni,quantidade,modo,codigoC,mes);
    return aux;
}

Produto newProd(Codigo codigo) {
    int i = 0;
    Produto aux = malloc(sizeof (struct produto));
    aux->codigo = strdup(codigo);
    aux->cliCompradores = NULL;
    aux->nVezesComprado = 0;
    aux->qtdComprada = 0;
    for (i = 0; i < 12; i++)
        aux->compradoMes[i] = 0;
    aux->left=aux->right=NULL;
    return aux;
}

Boolean Prod_compradoMes(Produto p, int mes) {
    if (p->compradoMes[mes - 1]) return 1;
    else return 0;
}

Boolean Cli_compraNoMes(Cliente c, int mes) {
    if (c->compraMes[mes - 1]) return 1;
    else return 0;
}

Codigo Prod_getCodigo(Produto p) {
    return strdup(p->codigo);
}

int Prod_getNVezesComprado(Produto p) {
    return p->nVezesComprado;
}

CodigoArray compradoresTraversal(struct simpleCli* comps, CodigoArray ca) {
    CodigoArray aux = ca;
    if (comps) {
        aux = compradoresTraversal(comps->left, aux);
        if (!CA_in(comps->codigo, aux))
            aux = CA_insert(aux, comps->codigo);
        aux = compradoresTraversal(comps->right, aux);
    } else return aux;
    return aux;
}

CodigoArray Prod_getCliCompradores(Produto p) {
    CodigoArray a = newCA();
    a = compradoresTraversal(p->cliCompradores, a);
    return a;
}



Cliente newCli(Codigo codigo) {
    int i;
    Cliente aux = malloc(sizeof (struct cliente));
    aux->codigo = strdup(codigo);
    aux->prodComprados = NULL;
    aux->nCompras = 0;
    for (i = 0; i < 12; i++)
        aux->compraMes[i] = 0;
    aux->left=aux->right=NULL;
    return aux;
}

Codigo Cli_getCodigo(Cliente c) {
    return strdup(c->codigo);
}
int Cli_getNCompras(Cliente c){
	return c->nCompras;
}
CodigoArray produtosTraversal(struct simpleProd* prods, CodigoArray ca) {
    CodigoArray aux = ca;
    if (prods) {
        aux = produtosTraversal(prods->left, aux);
        if (!CA_in(prods->codigo, aux))
            aux = CA_insert(aux, prods->codigo);
        aux = produtosTraversal(prods->right, aux);
    } else return aux;
    return aux;
}

CodigoArray Cli_getProdComprados(Cliente c) {
    CodigoArray a = newCA();
    produtosTraversal(c->prodComprados, a);
    return a;
}

int Cli_getCompras(Cliente c, int mes) {
    return c->compraMes[mes - 1];
}

int Cli_compraEmTodosOsMeses(Cliente c) {
    int i, flag = 1;
    for (i = 0; i < 12 && flag; i++)
        if (!(c->compraMes[i])) flag = 0;
    return flag;
}

int Prod_getVezesComprado(Produto p, int mes) {
    return p->compradoMes[mes - 1];
}

int Prod_getQuantidadeComprada(Produto p) {
    return p->qtdComprada;
}

int Prod_compradoEmTodosOsMeses(Produto p) {
    int i, flag = 1;
    for (i = 0; i < 12 && flag; i++)
        if (!(p->compradoMes[i])) flag = 0;
    return flag;
}



Produto Prod_getProduto(Produto p, Codigo codigoP){
Produto aux=p;
if(aux){
if(strcmp(aux->codigo,codigoP)>0) return Prod_getProduto(p->left,codigoP);
else if(strcmp(aux->codigo,codigoP)<0) return Prod_getProduto(p->right,codigoP);
else if(strcmp(aux->codigo,codigoP)==0) return aux;
}
return NULL;
}
struct simpleProd* sp_update(struct simpleProd* sp, int qtd, float valor, char modo, Codigo codigoP, int mes) {
    struct simpleProd* aux = sp;
    if (aux == NULL) {
        aux = newSP(codigoP, mes);
        if (modo == 'N') {
            aux->qtdCompN += qtd;
            aux->valorN += (qtd * valor);
        } else if (modo == 'P') {
            aux->qtdCompP += qtd;
            aux->valorP += (qtd * valor);
        }
        aux->qtdCompradaTotal += qtd;
        aux->valorTotal += (qtd * valor);
    } else if (strcmp(aux->codigo, codigoP) > 0) aux->left = sp_update(aux->left, qtd, valor, modo, codigoP, mes);
    else if (strcmp(aux->codigo, codigoP) < 0) aux->right = sp_update(aux->right, qtd, valor, modo, codigoP, mes);
    else if (strcmp(aux->codigo, codigoP) == 0) {
        if (aux->mes > mes) aux->left = sp_update(aux->left, qtd, valor, modo, codigoP, mes);
        else if (aux->mes < mes) aux->right = sp_update(aux->right, qtd, valor, modo, codigoP, mes);
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

struct simpleCli* sc_update(struct simpleCli* sc, int qtd, float valor, char modo, Codigo codigoC, int mes) {
    struct simpleCli* aux = sc;
    if (aux == NULL) {
        aux = newSC(codigoC, mes);
        if (modo == 'N') {
            aux->qtdCompN += qtd;
            aux->valorN += (qtd * valor);

        } else if (modo == 'P') {
            aux->qtdCompP += qtd;
            aux->valorP += (qtd * valor);

        }
        aux->qtdCompradaTotal += qtd;
        aux->valorTotal += (qtd * valor);
    } else if (strcmp(aux->codigo, codigoC) > 0) aux->left = sc_update(aux->left, qtd, valor, modo, codigoC, mes);
    else if (strcmp(aux->codigo, codigoC) < 0) aux->right = sc_update(aux->right, qtd, valor, modo, codigoC, mes);
    else if (strcmp(aux->codigo, codigoC) == 0) {
        if (aux->mes > mes) aux->left = sc_update(aux->left, qtd, valor, modo, codigoC, mes);
        else if (aux->mes < mes) aux->right = sc_update(aux->right, qtd, valor, modo, codigoC, mes);
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

Produto ProdT_updateProd(Produto pt, Codigo codigoP, int qtd, float valor, char modo, Codigo codigoC, int mes) {
    Produto aux = pt;
    Produto updat=Prod_getProduto(aux,codigoP);
    if (updat != NULL) {
        updat->nVezesComprado++;
        updat->compradoMes[mes - 1]++;
        updat->qtdComprada += qtd;
        updat->cliCompradores = sc_update(updat->cliCompradores, qtd, valor, modo, codigoC, mes);
    }
    return aux;
}


Cliente Cli_getCli(Cliente ct, Codigo codigoC){
Cliente aux=ct;
if(aux){
if(strcmp(aux->codigo,codigoC)>0) return Cli_getCli(ct->left,codigoC);
else if(strcmp(aux->codigo,codigoC)<0) return Cli_getCli(ct->right,codigoC);
else if(strcmp(aux->codigo,codigoC)==0) return aux;
}
return NULL;
}


Cliente ClienT_updateCli(Cliente ct, Codigo codigoP, int qtd, float valor, char modo, Codigo codigoC, int mes) {
    Cliente aux = ct;
    Cliente updat = Cli_getCli(aux, codigoC);
    if (updat != NULL) {
        updat->nCompras++;
        updat->compraMes[mes - 1]++;
        updat->prodComprados = sp_update(updat->prodComprados, qtd, valor, modo, codigoP, mes);
    }
    return aux;
}



ComprasDB newCDB() {
    ComprasDB aux = malloc(sizeof (struct comprasDB));
    aux->clientes = NULL;
    aux->compras = NULL;
    aux->produtos = NULL;
    return aux;
}

ComprasDB CDB_insertCliente(ComprasDB cdb, Codigo codigoC) {
    ComprasDB aux = cdb;
    aux->clientes = ClienT_insert(aux->clientes, codigoC);
    return aux;
}

ComprasDB CDB_insertProduto(ComprasDB cdb, Codigo codigoP) {
    ComprasDB aux = cdb;
    aux->produtos = ProdT_insert(aux->produtos, codigoP);
    return aux;
}



void CDB_dispose(ComprasDB cdb) {
    ClienT_dispose(cdb->clientes);
    CompT_dispose(cdb->compras);
    ProdT_dispose(cdb->produtos);
    free(cdb);
}

void ClienT_dispose(Cliente ct) {
    ClienT_dispose(ct->left);
    ClienT_dispose(ct->right);
    free(ct);
}

void ProdT_dispose(Produto pt) {
    ProdT_dispose(pt->left);
    ProdT_dispose(pt->right);
    free(pt);
}

void CompT_dispose(Compra ct) {
    CompT_dispose(ct->left);
    CompT_dispose(ct->right);
    free(ct);
}


TabelaCSV CDB_carregaClienteCSV(Cliente cli, TabelaCSV csv) {
int i;	
TabelaCSV aux=csv;
	Cliente auxC=cli;
	if(auxC){
	for(i=1;i<=12;i++)
		if (Cli_compraNoMes(cli, i)) aux = CSV_addCliente(aux, i);   
	aux=CDB_carregaClienteCSV(auxC->left,aux);
	aux=CDB_carregaClienteCSV(auxC->right,aux);
}
else return aux;
return aux;
}

TabelaCSV CDB_carregaClientesCSV(ComprasDB cdb, TabelaCSV csv) {
    TabelaCSV aux = csv;
    aux = CDB_carregaClienteCSV(cdb->clientes, aux);
    return aux;
}




Par procuraClientesSemCompras(Cliente ct, Par p){
	Par aux=p;
if(ct){
	if (ct->nCompras == 0) aux = Par_addCliente(aux);
	aux=procuraClientesSemCompras(ct->left,aux);
	aux=procuraClientesSemCompras(ct->right,aux);
}
else return aux;
return aux;
}

Par procuraNaoCompra(Cliente ct, Par p) {
    return procuraClientesSemCompras(ct, p);
}

Par procuraProdutosNaoComprados(Produto pt,Par p){
	Par aux=p;
if(pt){
	if(pt->nVezesComprado==0) aux=Par_addProduto(aux);
	aux=procuraProdutosNaoComprados(pt->left,aux);
	aux=procuraProdutosNaoComprados(pt->right,aux);
}
else return aux;
return aux;
}


Par procuraNaoComprado(Produto pt, Par p) {
    return procuraProdutosNaoComprados(pt, p);
}

Par CDB_procuraNaoUtilizados(ComprasDB cdb) {
    Par p = newPar();
    p = procuraNaoCompra(cdb->clientes, p);
    p = procuraNaoComprado(cdb->produtos, p);
    return p;
}

Table CDB_aux_carregaCompras(Table t, struct simpleProd* sp) {
    Table aux = t;
    if (sp) {

        aux = CDB_aux_carregaCompras(aux, sp->left);

        aux = CDB_aux_carregaCompras(aux, sp->right);

	aux = Tab_addValor(aux, sp->qtdCompradaTotal, sp->mes);    
} else return aux;
    return aux;
}

Table CDB_getTabelaCompras(ComprasDB cdb, Codigo codigo) {
    Table t = newTab(codigo);
    Cliente cli = Cli_getCli(cdb->clientes, codigo);
	if(cli)
    t = CDB_aux_carregaCompras(t, cli->prodComprados);
    return t;
}


ArvoreClientes CDB_carregaClientes_AC_aux(ArvoreClientes ac, struct simpleCli* sc) {
    ArvoreClientes aux = ac;
    if (sc) {
        aux = CDB_carregaClientes_AC_aux(aux, sc->left);
        aux = CDB_carregaClientes_AC_aux(aux, sc->right);
        if (sc->qtdCompN)
            aux = AC_insert(aux, sc->codigo, 'N');
        if (sc->qtdCompP)
            aux = AC_insert(aux, sc->codigo, 'P');


    } else return aux;
    return aux;
}

ListaDePCM CDB_clientesCompradores(ComprasDB cdb, Codigo codigo) {
    ArvoreClientes ac = newAC();
    Produto p = Prod_getProduto(cdb->produtos, codigo);
	if(p)
    ac = CDB_carregaClientes_AC_aux(ac, p->cliCompradores);
    return AC_travessiaArvore(ac, newLPCM());

}

TreeTop CDB_constroiTop(struct simpleProd* sp, TreeTop tt, int mes) {
    TreeTop aux = tt;
    if (sp) {
        if (mes == sp->mes) aux = TT_insertNode(aux, sp->codigo, sp->qtdCompradaTotal);
        aux = CDB_constroiTop(sp->left, aux, mes);
        aux = CDB_constroiTop(sp->right, aux, mes);
    } else return aux;
    return aux;
}


CodigoArray CDB_getTopComprasMensal(ComprasDB cdb, Codigo codigo, int mes) {
    Cliente cli = Cli_getCli(cdb->clientes, codigo);
    TreeTop aux = NULL;
	if(cli)
    aux = CDB_constroiTop(cli->prodComprados, aux, mes);
    return TT_maisComprados(aux, newCA());
}



CodigoArray compraTodos(Cliente cl,CodigoArray ca){
	CodigoArray aux=ca;
	if(cl){
	if (Cli_compraEmTodosOsMeses(cl)) aux = CA_insert(aux, Cli_getCodigo(cl));
        aux = compraTodos(cl->left, aux);
        aux = compraTodos(cl->right, aux);
}
	else return aux;
	return aux;
}

CodigoArray CDB_compraTodos(ComprasDB cdb) {
    CodigoArray aux = newCA();
    aux = compraTodos(cdb->clientes, aux);
    return aux;
}

ArvoreQtd constroiArvoreQtd(Produto prod, ArvoreQtd aq) {
    ArvoreQtd aux = aq;
    if (prod != NULL) {
        aux = AQ_insert(aux, Prod_getCodigo(prod), Prod_getQuantidadeComprada(prod));
        aux = constroiArvoreQtd(prod->left, aux);
        aux = constroiArvoreQtd(prod->right, aux);
    }
    return aux;
}

ArvoreQtd CDB_produtosToQtdArvore(ComprasDB cdb) {
    ArvoreQtd aux = newAQ();
    aux = constroiArvoreQtd(cdb->produtos,aux);
    return aux;
}

TreeTop constroiTopCompras_auxil(struct simpleProd* sp, TreeTop tt, CodigoArray ca) {
    TreeTop aux = tt;

    if (sp) {
        if (CA_in(sp->codigo, ca)) {
            aux = TT_update(aux, sp->codigo, sp->qtdCompradaTotal);
        } else {
            aux = TT_insertNode(aux, sp->codigo, sp->qtdCompradaTotal);
            ca = CA_insert(ca, sp->codigo);
            aux=constroiTopCompras_auxil(sp->left,tt,ca);
	    aux=constroiTopCompras_auxil(sp->right,tt,ca);
}
    } else return aux;
    return aux;
}

CodigoArray CDB_getTopCompras(ComprasDB cdb, Codigo codigo) {
    CodigoArray ca = newCA();
    TreeTop aux = NULL;
    Cliente cli = Cli_getCli(cdb->clientes, codigo);
    aux = constroiTopCompras_auxil(cli->prodComprados, aux, newCA());
    return TT_travessiaDecrescente(aux, ca);
}





Cliente ClienT_insert(Cliente ct, Codigo codigoC) {
    Cliente aux = ct;
    if(aux){
	if(strcmp(aux->codigo,codigoC)>0) aux->left=ClienT_insert(aux->left,codigoC);
	else if(strcmp(aux->codigo,codigoC)<0) aux->right=ClienT_insert(aux->right,codigoC);
}
    else aux=newCli(codigoC);
    return aux;
}


Produto ProdT_insert(Produto pt, Codigo codigoP) {
    Produto aux = pt;
    if(aux){
	if(strcmp(aux->codigo,codigoP)>0) aux->left=ProdT_insert(aux->left,codigoP);
	else if(strcmp(aux->codigo,codigoP)<0) aux->right=ProdT_insert(aux->right,codigoP);
}
    else aux=newProd(codigoP);
    return aux;
}

ComprasDB CDB_registerSale(ComprasDB cdb, Codigo codigoP, float valor, int qtd, char modo, Codigo codigoC, int mes) {
    ComprasDB aux = cdb;
    aux->compras = CompT_insert(aux->compras, codigoP, valor, qtd, modo, codigoC, mes);
    aux->produtos = ProdT_updateProd(aux->produtos, codigoP, qtd, valor, modo, codigoC, mes);
    aux->clientes = ClienT_updateCli(aux->clientes, codigoP, qtd, valor, modo, codigoC, mes);
    return aux;
}
