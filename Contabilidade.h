/* 
 * File:   Contabilidade.h
 * Author: Pedro Cunha
 *
 * Created on 6 de Março de 2015, 16:56
 */

#ifndef CONTABILIDADE_H
#define	CONTABILIDADE_H
#include "Codigo.h"
typedef struct contnode_* Contab;
Contab new(Codigo codigo);
Contab insert(Contab cont, Codigo codigo);
void dispose(Contab nodo);
Contab insereCompra(Contab c, Codigo codigo, char modo, int qtd, float valor, int mes);
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

typedef struct auxR2* AuxR2;
AuxR2 new(int vendasN,int vendasP,float fatura);
int getVendasN(AuxR2 aux);
int getVendasP(AuxR2 aux);
float getFaturacaoT(AuxR2 aux);
AuxR2 getDadosProduto(CTree ct, Codigo codigo, int mes);
#endif

