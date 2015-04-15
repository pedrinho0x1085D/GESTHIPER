/** 
 * File:   GHDB.h
 * Author: Pedro Cunha
 * Camada de Convergência
 * Created on 6 de Março de 2015, 16:56
 */

#ifndef GHDB_H
#define	GHDB_H
#include "EstruturasAux.h"
#include "Compras.h"
#include "CusTypes.h"

typedef struct db* GHDB;

GHDB new();
GHDB insertProd(GHDB db, Codigo codigo);
GHDB insertCli(GHDB db, Codigo codigo);
GHDB insertComp(GHDB db, Codigo codigoP, float valor, int qtd, char modo, Codigo codigoC, int mes);
CodigoArray getClientes(GHDB db, Codigo primeira_letra);
CodigoArray getProdutos(GHDB db, Codigo primeira_letra);
AuxR2 getContabilidadeProduto(GHDB db, Codigo produto, int mes);
CodigoArray getProdutosNuncaComprados(GHDB db);
Table getTabelaProdutos(GHDB db,Codigo codigo);
TabelaCSV getRelacao(GHDB db);
Par procuraNaoUtilizados(GHDB db);
AuxQ7 criaLista(GHDB db, int lower,int higher);
CodigoArray getCompraEmTodosOsMeses(GHDB db);
CodigoArray getTopCompras(GHDB db, Codigo codigo);
CodigoArray getTopComprasMensal(GHDB db, Codigo codigo, int mes);
/*CodigoArray getClientesCompradores(GHDB db,Codigo codigo);
CodigoArray getNMaisVendidos(GHDB db, int n);*/
Boolean prodFileIsLoaded(GHDB db);
Boolean cliFileIsLoaded(GHDB db);
Boolean comFileIsLoaded(GHDB db);
Boolean allFilesLoaded(GHDB db);
Boolean prodCodeNotExistent(GHDB db, Codigo codigoP);
Boolean cliCodeNotExistent(GHDB db, Codigo codigoC);
void loadProdFile(GHDB db);
void loadCliFile(GHDB db);
void loadComFile(GHDB db);
void disposeReload(GHDB db);
void disposeExit(GHDB db);
#endif	/* GHDB_H */

