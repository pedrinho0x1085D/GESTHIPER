/* 
 * File:   Catalog.h
 * Author: Pedro Cunha
 *
 * Created on 6 de Março de 2015, 16:56
 */

#ifndef CATALOG_H
#define	CATALOG_H

#include "AVLTree.h"

/*ESTRUTURAS DE DADOS PÃšBLICAS*****************************************/
typedef struct Catalog_ *Catalog;


/*FUNÃ‡Ã•ES PÃšBLICAS*****************************************************/
Catalog new();
int dispose(Catalog index);
int insert(Catalog index, char *codigo);
int getNumCodigos(Catalog index);
ArvoreAVL getTree(Catalog index, char *primeira_letra);
CodigoArray getTreeToArray(Catalog c, char* codigo);
int searchCode(Catalog c,char* codigo);

#endif	/* CATALOG_H */

