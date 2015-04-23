
#include "AVLTree.h"
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

struct produtoTree {
    ArvoreAVL arvore;
};

struct clienteTree {
    ArvoreAVL arvore;
};
struct compratree {
    ArvoreAVL arvore;
};

struct comprasDB {
    CompraTree compras;
    ClienteTree clientes;
    ProdutoTree produtos;
};

int comparatorCompra(const void* valor1, const void* valor2) {
    int i;
	const Compra c1=(const Compra)valor1,c2=(const Compra)valor2;
    if (c1->mes != c2->mes) return c1->mes - c2->mes;
    else {
	i=strcmp(c1->codigoC,c2->codigoC);
	if(i) return i;
	else{
	i=strcmp(c1->codigoP,c2->codigoC);
	if(i) return i;
}
}

    return -1;
}

int comparatorCliente(const void* valor1, const void* valor2) {
    return strcmp(((Cliente)valor1)->codigo, ((Cliente)valor2)->codigo);
	return 1;
}

int comparatorProduto(const void* valor1, const void* valor2) {
    return strcmp(((Produto)valor1)->codigo, ((Produto)valor2)->codigo);
	return 1;
}

Compra newComp(Codigo codigoP, float valorUni, int quantidade, char modo, Codigo codigoC, int mes) {
    Compra aux = malloc(sizeof (struct compra));
    aux->codigoP = strdup(codigoP);
    aux->valorUni = valorUni;
    aux->quantidade = quantidade;
    aux->modo = modo;
    aux->codigoC = strdup(codigoC);
    aux->mes = mes;
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



void destroi(void* valor1) {
    free(valor1);
}



CompraTree newCompT() {
    CompraTree aux = malloc(sizeof (struct compratree));
    aux->arvore = cria_ArvoreAVL(&comparatorCompra, &destroi);
    return aux;
}

ClienteTree newClienT() {
    ClienteTree aux = malloc(sizeof (struct clienteTree));
    aux->arvore = cria_ArvoreAVL(&comparatorCliente, &destroi);
    return aux;
}

ProdutoTree newProdT() {
    ProdutoTree aux = malloc(sizeof (struct produtoTree));
    aux->arvore = cria_ArvoreAVL(&comparatorProduto, &destroi);
    return aux;
}

CompraTree CompT_insertC(CompraTree ct, Compra c) {
    CompraTree aux = ct;
    insere_ArvoreAVL(aux->arvore, c);
    return aux;
}

CompraTree CompT_insert(CompraTree ct, Codigo codigoP, float valorUni, int quantidade, char modo, Codigo codigoC, int mes) {
    CompraTree aux = ct;
    Compra c = newComp(codigoP, valorUni, quantidade, modo, codigoC, mes);
    insere_ArvoreAVL(aux->arvore, c);
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


CodigoArray Prod_getCliCompradores(Produto p) {
    CodigoArray a = newCA();
    a=compradoresTraversal(p->cliCompradores, a);
    return a;
}

CodigoArray compradoresTraversal(struct simpleCli* comps, CodigoArray ca) {
    CodigoArray aux = ca;
    if (comps) {
        aux = compradoresTraversal(comps->left, aux);
        if(!CA_in(comps->codigo,aux))
		aux = CA_insert(aux, comps->codigo);
        aux = compradoresTraversal(comps->right, aux);
    } else return aux;
    return aux;
}




Cliente newCli(Codigo codigo) {
    int i;
    Cliente aux = malloc(sizeof (struct cliente));
    aux->codigo = strdup(codigo);
    aux->prodComprados = NULL;
    aux->nCompras = 0;
    for (i = 0; i < 12; i++)
        aux->compraMes[i] = 0;
    return aux;
}

Codigo Cli_getCodigo(Cliente c) {
    return strdup(c->codigo);
}

int Cli_getNVezesComprado(Cliente c) {
    return c->nCompras;
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

int Prod_getQuantidadeComprada(Produto p){
    return p->qtdComprada;
}

int Prod_compradoEmTodosOsMeses(Produto p) {
    int i, flag = 1;
    for (i = 0; i < 12 && flag; i++)
        if (!(p->compradoMes[i])) flag = 0;
    return flag;
}

CodigoArray produtosTraversal(struct simpleProd* prods, CodigoArray ca) {
    CodigoArray aux = ca;
    if (prods) {
        aux = produtosTraversal(prods->left, aux);
        if(!CA_in(prods->codigo,aux))
		aux = CA_insert(aux, prods->codigo);
        aux = produtosTraversal(prods->right, aux);
    } else return aux;
    return aux;
}






ProdutoTree ProdT_updateProdTree(ProdutoTree pt, Codigo codigoP, int qtd, float valor, char modo, Codigo codigoC, int mes) {
    ProdutoTree aux = pt;
    Produto updat = getProd(aux->arvore, codigoP);
    if (updat != NULL) {
        updat->nVezesComprado++;
        updat->compradoMes[mes - 1]++;
        updat->qtdComprada += qtd;
        updat->cliCompradores = sc_update(updat->cliCompradores, qtd, valor, modo, codigoC, mes);
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

ClienteTree ClienT_updateCliTree(ClienteTree ct, Codigo codigoP, int qtd, float valor, char modo, Codigo codigoC, int mes) {
    ClienteTree aux = ct;
    Cliente updat = getCli(ct->arvore, codigoC);
    if (updat != NULL) {
        updat->nCompras++;
        updat->compraMes[mes - 1]++;
        updat->prodComprados = sp_update(updat->prodComprados, qtd, valor, modo, codigoP, mes);
    }
    return aux;
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


ComprasDB newCDB() {
    ComprasDB aux = malloc(sizeof (struct comprasDB));
    aux->clientes = newClienT();
    aux->compras = newCompT();
    aux->produtos = newProdT();
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

ComprasDB CDB_registerSale(ComprasDB cdb, Codigo codigoP, float valor, int qtd, char modo, Codigo codigoC, int mes) {
    ComprasDB aux = cdb;
    aux->compras = CompT_insert(aux->compras, codigoP, valor, qtd, modo, codigoC, mes);
    aux->produtos = ProdT_updateProdTree(aux->produtos, codigoP, qtd, valor, modo, codigoC, mes);
    aux->clientes = ClienT_updateCliTree(aux->clientes, codigoP, qtd, valor, modo, codigoC, mes);
    return aux;
}

void CDB_dispose(ComprasDB cdb) {
    ClienT_dispose(cdb->clientes);
    CompT_dispose(cdb->compras);
    ProdT_dispose(cdb->produtos);
    free(cdb);
}

void ClienT_dispose(ClienteTree ct) {
    destroi_ArvoreAVL(ct->arvore);
    free(ct);
}

void ProdT_dispose(ProdutoTree pt) {
    destroi_ArvoreAVL(pt->arvore);
    free(pt);
}

void CompT_dispose(CompraTree ct) {
    destroi_ArvoreAVL(ct->arvore);
    free(ct);
}

TabelaCSV CDB_carregaClientesCSV(ComprasDB cdb, TabelaCSV csv) {
    TabelaCSV aux = csv;
    aux = carregaClientesCSV_AUX(cdb->clientes->arvore, aux);
    return aux;
}

TabelaCSV CDB_carregaCliente(TabelaCSV csv, Cliente cli) {
    int i;
    TabelaCSV aux = csv;
    for (i = 1; i <= 12; i++)
        if (Cli_compraNoMes(cli, i)) aux = CSV_addCliente(aux, i);
    return aux;
}

Par CDB_procuraNaoUtilizados(ComprasDB cdb) {
    Par p = newPar();
    p = procuraNaoCompra(cdb->clientes, p);
    p = procuraNaoComprado(cdb->produtos, p);
    return p;
}

  Par procuraNaoCompra(ClienteTree ct, Par p) {
    return procuraClientesSemCompras(ct->arvore, p);
}

  Par procuraNaoComprado(ProdutoTree pt, Par p) {
    return procuraProdutosNaoComprados(pt->arvore, p);
}

Table CDB_getTabelaCompras(ComprasDB cdb, Codigo codigo) {
    Table t = newTab(codigo);
    Cliente cli = getCli(cdb->clientes->arvore, codigo);
    t = CDB_aux_carregaCompras(t, cli->prodComprados);
    return t;
}

  Table CDB_aux_carregaCompras(Table t, struct simpleProd* sp) {
    Table aux = t;
    if (sp) {
        aux = Tab_addValor(aux, sp->qtdCompradaTotal, sp->mes);
        aux = CDB_aux_carregaCompras(aux, sp->left);
        aux = CDB_aux_carregaCompras(aux, sp->right);
    } else return aux;
    return aux;
}

ListaDePCM clientesCompradores(ComprasDB cdb, Codigo codigo) {
    ArvoreClientes ac = newAC();
    Produto p = getProd(cdb->produtos->arvore, codigo);
    ac = CDB_carregaClientes(ac, p->cliCompradores);
    return AC_travessiaArvore(ac, newLPCM());

}

  ArvoreClientes CDB_carregaClientes(ArvoreClientes ac, struct simpleCli* sc) {
    ArvoreClientes aux = ac;
    if (sc) {
	aux= CDB_carregaClientes(aux,sc->left);
        aux= CDB_carregaClientes(aux,sc->right);
        if (sc->qtdCompN)
            aux = AC_insert(aux,sc->codigo, 'N');
        if (sc->qtdCompP)
            aux = AC_insert(aux,sc->codigo, 'P');
        
        
        }
    else return aux;
    return aux;
}

CodigoArray getTopComprasMensal(ComprasDB cdb,Codigo codigo,int mes){
    Cliente cli=getCli(cdb->clientes->arvore,codigo);
    TreeTop aux=NULL;
    aux=CDB_constroiTop(cli->prodComprados,aux,mes);
    return TT_maisComprados(aux,newCA());
}

  TreeTop CDB_constroiTop(struct simpleProd* sp, TreeTop tt, int mes){
    TreeTop aux=tt;
    if(sp){
        if(mes==sp->mes) aux=TT_insertNode(aux,sp->codigo,sp->qtdCompradaTotal);
        aux=CDB_constroiTop(sp->left,aux,mes);
        aux=CDB_constroiTop(sp->right,aux,mes);
    }
    else return aux;
    return aux;
}

CodigoArray CDB_compraTodos(ComprasDB cdb){
    CodigoArray aux=newCA();
    aux=compraTodos(cdb->produtos->arvore,aux);
    return aux;
}

ArvoreQtd CDB_produtosToQtdArvore(ComprasDB cdb){
    ArvoreQtd aux=newAQ();
    aux=constroiArvoreQtd(cdb->produtos->arvore);
    return aux;
}

CodigoArray CDB_getTopCompras(ComprasDB cdb,Codigo codigo){
    CodigoArray ca=newCA();
    TreeTop aux=NULL;
    Cliente cli=getCli(cdb->clientes->arvore,codigo);
    aux=constroiTopCompras(cli->prodComprados,aux,newCA());
    return TT_travessiaDecrescente(aux,ca);
}

  TreeTop constroiTopCompras(struct simpleProd* sp,TreeTop tt,CodigoArray ca){
    TreeTop aux=tt;
    
    if(sp){
        if(CA_in(sp->codigo,ca)){
            aux=TT_update(aux,sp->codigo,sp->qtdCompradaTotal);
        }
        else{
            aux=TT_insertNode(aux,sp->codigo,sp->qtdCompradaTotal);
            ca=CA_insert(ca,sp->codigo);
        }
    }
    else return aux;
    return aux;
}

ClienteTree ClienT_insertC(ClienteTree ct, Cliente c) {
    ClienteTree aux = ct;
    insere_ArvoreAVL(aux->arvore, c);
    return aux;
}

ClienteTree ClienT_insert(ClienteTree ct, Codigo codigoC) {
    ClienteTree aux = ct;
    Cliente c = newCli(codigoC);
    insere_ArvoreAVL(aux->arvore, c);
    return aux;
}

ProdutoTree ProdT_insertP(ProdutoTree pt, Produto p) {
    ProdutoTree aux = pt;
    insere_ArvoreAVL(aux->arvore, p);
    return aux;
}

ProdutoTree ProdT_insert(ProdutoTree pt, Codigo codigoP) {
    ProdutoTree aux = pt;
    Produto p = newProd(codigoP);
    insere_ArvoreAVL(aux->arvore, p);
    return aux;
}
