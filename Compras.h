/* 
 * File:   Compras.h
 * Author: Pedro Cunha
 *
 * Created on 6 de Março de 2015, 16:56
 */

#ifndef COMPRAS_H
#define	COMPRAS_H
#include "Codigo.h"

typedef struct compra* Compra;
Compra new(char* codigoP, float valorUni, int quantidade, char modo, char* codigoC, int mes);
char* getCodigoP(Compra com);
float getValorUni(Compra com);
int getQuantidade(Compra com);
char getModo(Compra com);
char* getCodigoC(Compra com);
int getMes(Compra com);
int equals(Compra c1, Compra c2);

typedef struct compratree* CompraTree;
CompraTree new();
void insert(CompraTree ct, Compra c);
void insert(CompraTree ct, char* codigoP, float valorUni, int quantidade, char modo, char* codigoC, int mes);
void updateProdTree(ProdutoTree pt, char* codigoP, int qtd, float valor, char modo, char* codigoC, int mes);
void updateCliTree(ClienteTree ct, char* codigoP, int qtd, float valor, char modo, char* codigoC, int mes);

typedef struct produto* Produto;
Produto new(char* codigo);
char* getCodigo(Produto p);
int getNVezesComprado(Produto p);
CodigoArray getCliCompradores(Produto p);
int getVezesComprado(Produto p, int mes);
int compradoEmTodosOsMeses(Produto p);

typedef struct cliente* Cliente;
char* getCodigo(Cliente c);
int getNCompras(Produto p);
CodigoArray getProdComprados(Produto p);
int getCompras(Cliente c, int mes);
int compraEmTodosOsMeses(Cliente c);

typedef struct produtoTree* ProdutoTree;
ProdutoTree new();
void insert(ProdutoTree pt, Produto p);
void insert(ProdutoTree pt, char* codigoP);

typedef struct clienteTree* ClienteTree;
ClienteTree new();
void insert(ClienteTree ct, Cliente c);
void insert(ClienteTree ct, char* codigoC);
void dispose(ClienteTree ct);
void dispose(CompraTree ct);
void dispose(ProdutoTree pt);
CodigoArray nuncaComprados(ComprasDB cdb);

typedef struct comprasDB* ComprasDB;
ComprasDB new();
void insertCliente(ComprasDB cdb, char* codigoC);
void insertProduto(ComprasDB cdb, char* codigoP);
void registerSale(ComprasDB cdb, char* codigoP, float valor, int qtd, char modo, char* codigoC, int mes);
void dispose(ComprasDB cdb);

typedef struct tabela* Table;
Table new(char* codigo);
void addValor(Table t, int qtd, int mes);
char* getCodigo(Table t);
int getCompras(Table t, int mes);
void dispose(Table t);
void toTxtFile(Table t,char* filename);
Table getTabelaCompras(ComprasDB dbc,char* codigo);
void constroiTabela(Cliente cli, Table tab);

typedef struct tableQ11* TabelaCSV;
TabelaCSV new();
void add(TabelaCSV tcsv, int mes, int qtd);
void dispose(TabelaCSV tcsv);
TabelaCSV getRelacao(ComprasDB cdb);
void toCsvFile(TabelaCSV csv,char* filename);

typedef struct par* Par;
Par new();
Par dispose(Par p);
void addCliente(Par p);
void addProduto(Par p);
int getClientesSemCompras(Par p);
int getProdutosNaoComprados(Par p);
Par procuraNaoUtilizados(ComprasDB dbc);

int in(int x,int linf,int lsup);

typedef struct auxilQ7* AuxQ7;
AuxQ7 new();
void dispose(AuxQ7 aux);
float getFaturacao(AuxQ7 aux);
int getNCompras(AuxQ7 aux);
void insereCompra(AuxQ7 auxil, float valor,int qtd);
AuxQ7 criaLista(ComprasDB cdb, int lower,int higher);

CodigoArray compraTodos(ComprasDB cdb);

#endif

