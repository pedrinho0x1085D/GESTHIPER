/*
 *        __      __   ______
 *       / /     / /  |____  \
 *      / /     / /     ___| |
 *     / /     / /     |___  |
 *    / /___  / /      ____| |
 *   /_____/ /_/      |______/
 *
 *
 *  Ficheiro: GHDB.h
 *
 */

#ifndef GHDB_H
#define	GHDB_H
#include "EstruturasAux.h"
#include "Compras.h"
#include "CusTypes.h"

typedef struct db* GHDB;

GHDB newGHDB();
GHDB GHDB_insertProd(GHDB db, Codigo codigo);
GHDB GHDB_insertCli(GHDB db, Codigo codigo);
GHDB GHDB_insertComp(GHDB db, Codigo codigoP, float valor, int qtd, char modo, Codigo codigoC, int mes);
CodigoArray GHDB_getClientes(GHDB db, Codigo primeira_letra);
CodigoArray GHDB_getProdutos(GHDB db, Codigo primeira_letra);
VendasProduto GHDB_getContabilidadeProduto(GHDB db, Codigo produto, int mes);
CodigoArray GHDB_getProdutosNuncaComprados(GHDB db);
Table GHDB_getTabelaProdutos(GHDB db,Codigo codigo);
TabelaCSV GHDB_getRelacao(GHDB db);
Par GHDB_procuraNaoUtilizados(GHDB db);
Faturacao GHDB_criaLista(GHDB db, int lower,int higher);
CodigoArray GHDB_getCompraEmTodosOsMeses(GHDB db);
CodigoArray GHDB_getTopCompras(GHDB db, Codigo codigo);
CodigoArray GHDB_getTopComprasMensal(GHDB db, Codigo codigo, int mes);
ListaDePCM GHDB_getClientesCompradores(GHDB db,Codigo codigo);
CodigoArray GHDB_getNMaisVendidos(GHDB db, int n);
Boolean GHDB_prodFileIsLoaded(GHDB db);
Boolean GHDB_cliFileIsLoaded(GHDB db);
Boolean GHDB_comFileIsLoaded(GHDB db);
Boolean GHDB_allFilesLoaded(GHDB db);
Boolean GHDB_prodCodeNotExistent(GHDB db, Codigo codigoP);
Boolean GHDB_cliCodeNotExistent(GHDB db, Codigo codigoC);
GHDB GHDB_loadProdFile(GHDB db);
GHDB GHDB_loadCliFile(GHDB db);
GHDB GHDB_loadComFile(GHDB db);
GHDB GHDB_disposeReload(GHDB db);
void GHDB_disposeExit(GHDB db);
#endif	/* GHDB_H */

