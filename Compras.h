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
typedef struct cliente* Cliente;
char* getCodigo(Cliente c);
int getNCompras(Produto p);
CodigoArray getProdComprados(Produto p);
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
#endif

