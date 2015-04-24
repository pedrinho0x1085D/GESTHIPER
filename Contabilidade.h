/*
 *        __      __   ______
 *       / /     / /  |____  \
 *      / /     / /     ___| |
 *     / /     / /     |___  |
 *    / /___  / /      ____| |
 *   /_____/ /_/      |______/
 *
 *
 *  Ficheiro: Contabilidade.h
 *
 */

#ifndef CONTABILIDADE_H
#define	CONTABILIDADE_H
#include "EstruturasAux.h"
#include "CusTypes.h"
typedef struct contnode_* Contab;
typedef struct arvoreContabil* CTree;
Contab newCont(Codigo codigo);
Contab Cont_insert(Contab cont, Codigo codigo);
void Cont_dispose(Contab nodo);
Contab Cont_insereCompra(Contab c, Codigo codigo, char modo, int qtd, float valor, int mes);
Boolean Cont_naoCompradoNoAno(Contab ct);
float Cont_getFaturacaoNormal(Contab c, Codigo codigo, int mes);
float Cont_getFaturacaoPromo(Contab c, Codigo codigo, int mes);
int Cont_getVendasNormal(Contab c, Codigo codigo, int mes);
int Cont_getVendasPromo(Contab c, Codigo codigo, int mes);
int Cont_getNVendasNormal(Contab c, Codigo codigo, int mes);
int Cont_getNVendasPromo(Contab c, Codigo codigo, int mes);
int hashFuncCont(Codigo codigo);
CTree CT_insert(CTree ct, Codigo codigo);
CTree newCT();
void CT_dispose(CTree nodo);
CTree CT_insereCompra(CTree ct, Codigo codigo, char modo, int qtd, float valor, int mes);
float CT_getFaturacaoNormal(CTree ct, Codigo codigo, int mes);
float CT_getFaturacaoPromo(CTree ct, Codigo codigo, int mes);
int CT_getVendasNormal(CTree ct, Codigo codigo, int mes);
int CT_getVendasPromo(CTree ct, Codigo codigo, int mes);
int CT_getNVendasNormal(CTree ct, Codigo codigo, int mes);
int CT_getNVendasPromo(CTree ct, Codigo codigo, int mes);

VendasProduto CT_getDadosProduto(CTree ct, Codigo codigo, int mes);
VendasProduto Cont_getDadosProduto(Contab c, Codigo codigo, int mes);
TabelaCSV CT_carregaCompras(CTree ct, TabelaCSV csv);
TabelaCSV Cont_carregaCompras(Contab cont, TabelaCSV csv);

CodigoArray CT_produtosNaoComprados(CTree ct);
CodigoArray Cont_insereProdutosNaoComprados(Contab ct, CodigoArray ca);
Faturacao Cont_carregaLista(Contab ct, int lower, int higher, Faturacao ft);
Faturacao CT_criaLista(CTree ct, int lower, int higher);
#endif

