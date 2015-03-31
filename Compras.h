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
Compra new(char* codigoP,float valorUni, int quantidade,char modo,char* codigoC,int mes);
char* getCodigoP(Compra com);
float getValorUni(Compra com);
int getQuantidade(Compra com);
char getModo(Compra com);
char* getCodigoC(Compra com);
int getMes(Compra com);
int equals(Compra c1,Compra c2);
typedef struct compratree* CompraTree;
CompraTree new();
void insert(CompraTree ct,Compra c);
void insert(CompraTree ct, char* codigoP,float valorUni, int quantidade,char modo,char* codigoC,int mes);

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
typedef struct clienteTree* ClienteTree;
ClienteTree new();
#endif

