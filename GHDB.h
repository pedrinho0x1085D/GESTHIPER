/* 
 * File:   GHDB.h
 * Author: Pedro Cunha
 *
 * Created on 6 de Março de 2015, 16:56
 */

#ifndef GHDB_H
#define	GHDB_H
#include "Codigo.h"
#include "Compras.h"

typedef struct db* GHDB;

GHDB new();
void insertProd(GHDB db, char* codigo);
void insertCli(GHDB db, char* codigo);
void insertComp(GHDB db, char* codigoP, float valor, int qtd, char modo, char* codigoC, int mes);
CodigoArray getClientes(GHDB db, char* primeira_letra);
CodigoArray getProdutos(GHDB db, char* primeira_letra);
AuxR2 getContabilidadeProduto(GHDB db, char* produto, int mes);
CodigoArray getProdutosNuncaComprados(GHDB db);
Table getTabelaProdutos(GHDB db,char* codigo);
TabelaCSV getRelacao(GHDB db);
Par procuraNaoUtilizados(GHDB db);
AuxQ7 criaLista(GHDB db, int lower,int higher);
CodigoArray getCompraEmTodosOsMeses(GHDB db);
CodigoArray getTopCompras(GHDB db, char* codigo);
CodigoArray getTopComprasMensal(GHDB db, char* codigo, int mes);
CodigoArray getClientesCompradores(GHDB db,char* codigo);
int prodFileIsLoaded(GHDB db);
int cliFileIsLoaded(GHDB db);
int comFileIsLoaded(GHDB db);
int allFilesLoaded(GHDB db);
void loadProdFile(GHDB db);
void loadCliFile(GHDB db);
void loadComFile(GHDB db);
void disposeReload(GHDB db);
void disposeExit(GHDB db);
#endif	/* GHDB_H */

