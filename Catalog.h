/*
 *        __      __   ______
 *       / /     / /  |____  \
 *      / /     / /     ___| |
 *     / /     / /     |___  |
 *    / /___  / /      ____| |
 *   /_____/ /_/      |______/
 *
 *
 *  Ficheiro: Catalog.h
 *
 */

#ifndef CATALOG_H
#define	CATALOG_H


#include "EstruturasAux.h"
#include "CusTypes.h"

/*ESTRUTURAS DE DADOS PÃšBLICAS*****************************************/
typedef struct Catalog_ *Catalog;
typedef struct TreeCatNode *TreeCat;
/*FUNÃ‡Ã•ES PÃšBLICAS*****************************************************/
/**
 * Inicialização de um objecto do tipo Catalog
 * @return Novo Objecto
 */
Catalog newCat();
TreeCat newNode(Codigo c);
void disposeTreeCatC(TreeCat t);
TreeCat TreeCat_insert(TreeCat t,Codigo c);

/**
 * Apagamento de um Catalog
 * @param index Objecto a ser removido
 */
void Cat_dispose(Catalog index);
/**
 * Inserção de um código no Catálogo
 * @param index Catálogo
 * @param codigo Código a ser inserido
 * 
 */
Catalog Cat_insert(Catalog index, char *codigo);
/**
 * Retorna o número de Códigos existentes no Catálogo
 * @param index Catálogo a ser consultado
 * @return 
 */
int Cat_getNumCodigos(Catalog index,Codigo c);


/**
 * Retorna um CodigoArray com os códigos ordenados alfabeticamente
 * @param c Catálogo a ser consultado
 * @param codigo Código a ser utilizado na procura
 * @return Array de Códigos com os códigos ordenados alfabeticamente
 */
CodigoArray Cat_getTreeCatCatoArray(Catalog c, Codigo codigo);
/**
 * Procura um código no Catálogo
 * @param c Catálogo a ser consultado
 * @param codigo Termo de procura
 * @return 1 Caso o codigo exista, 0 caso contrário
 */
Boolean Cat_searchCode(Catalog c, Codigo codigo);
CodigoArray Cat_getTreeToArray(Catalog c, Codigo codigo);
#endif	/* CATALOG_H */

