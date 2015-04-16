/* 
 * File:   Contabilidade.h
 * Author: Pedro Cunha
 *
 * Created on 6 de Março de 2015, 16:56
 */

#ifndef CONTABILIDADE_H
#define	CONTABILIDADE_H
#include "EstruturasAux.h"
typedef struct contnode_* Contab;
Contab new(Codigo codigo);
Contab insert(Contab cont, Codigo codigo);
void dispose(Contab nodo);
Contab insereCompra(Contab c, Codigo codigo, char modo, int qtd, float valor, int mes);
Boolean naoCompradoNoAno(Contab ct);
float getFaturacaoNormal(Contab c, Codigo codigo, int mes);
float getFaturacaoPromo(Contab c, Codigo codigo, int mes);
int getVendasNormal(Contab c, Codigo codigo, int mes);
int getVendasPromo(Contab c, Codigo codigo, int mes);
int getNVendasNormal(Contab c, Codigo codigo, int mes);
int getNVendasPromo(Contab c, Codigo codigo, int mes);
typedef struct arvoreContabil* CTree;
CTree insert(CTree ct, Codigo codigo);
CTree new();
void dispose(CTree nodo);
CTree insereCompra(CTree ct, Codigo codigo, char modo, int qtd, float valor, int mes);
float getFaturacaoNormal(CTree ct, Codigo codigo, int mes);
float getFaturacaoPromo(CTree ct, Codigo codigo, int mes);
int getVendasNormal(CTree ct, Codigo codigo, int mes);
int getVendasPromo(CTree ct, Codigo codigo, int mes);
int getNVendasNormal(CTree ct, Codigo codigo, int mes);
int getNVendasPromo(CTree ct, Codigo codigo, int mes);

VendasProduto getDadosProduto(CTree ct, Codigo codigo, int mes) ;
TabelaCSV carregaCompras(CTree ct, TabelaCSV csv);
TabelaCSV carregaCompras(Contab cont, TabelaCSV csv);

CodigoArray produtosNaoComprados(CTree ct);

Faturacao criaLista(CTree ct,int lower,int higher);
#endif

