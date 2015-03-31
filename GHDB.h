/* 
 * File:   GHDB.h
 * Author: Pedro Cunha
 *
 * Created on 6 de Março de 2015, 16:56
 */

#ifndef GHDB_H
#define	GHDB_H
#include "AVLTree.h"
#include "Catalog.h"

typedef struct db* GHDB;

GHDB new();
void insertProd(GHDB db, char* codigo);
void insertCli(GHDB db, char* codigo);
ArvoreAVL getClientes(GHDB db, char* primeira_letra);
ArvoreAVL getProdutos(GHDB db, char* primeira_letra);
int prodFileIsLoaded(GHDB db);
int cliFileIsLoaded(GHDB db);
int comFileIsLoaded(GHDB db);
int allFilesLoaded(GHDB db);
void loadProdFile(GHDB db);
void loadCliFile(GHDB db);
void loadComFile(GHDB db);

#endif	/* GHDB_H */

