/* 
 * File:   Catalog.h
 * Author: Pedro Cunha
 *
 * Created on 6 de Março de 2015, 16:56
 */

#ifndef CATALOG_H
#define	CATALOG_H

#include "AVLTree.h"
#include "EstruturasAux.h"
#include "CusTypes.h"

/*ESTRUTURAS DE DADOS PÃšBLICAS*****************************************/
typedef struct Catalog_ *Catalog;


/*FUNÃ‡Ã•ES PÃšBLICAS*****************************************************/
/**
 * Inicialização de um objecto do tipo Catalog
 * @return Novo Objecto
 */
Catalog newCat();
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
int Cat_getNumCodigos(Catalog index);
/**
 * Retorna a árvore AVL relativa a uma letra
 * @param index Catálogo a ser consultado
 * @param primeira_letra Letra a ser utilizada na procura
 * @return Árvore AVL relativa à letra indicada por primeira_letra.
 */
ArvoreAVL Cat_getTree(Catalog index, char *primeira_letra);
/**
 * Retorna um CodigoArray com os códigos ordenados alfabeticamente
 * @param c Catálogo a ser consultado
 * @param codigo Código a ser utilizado na procura
 * @return Array de Códigos com os códigos ordenados alfabeticamente
 */
CodigoArray Cat_getTreeToArray(Catalog c, Codigo codigo);
/**
 * Procura um código no Catálogo
 * @param c Catálogo a ser consultado
 * @param codigo Termo de procura
 * @return 1 Caso o codigo exista, 0 caso contrário
 */
Boolean Cat_searchCode(Catalog c, Codigo codigo);

#endif	/* CATALOG_H */

