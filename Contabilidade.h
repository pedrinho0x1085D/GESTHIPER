/* 
 * File:   Contabilidade.h
 * Author: Pedro Cunha
 *
 * Created on 6 de Março de 2015, 16:56
 */

#ifndef CONTABILIDADE_H
#define	CONTABILIDADE_H

typedef struct contnode_* Contab;
Contab new(char* codigo);
void insert(Contab cont, char *codigo);
void dispose(Contab nodo);
void insereCompra(Contab c, char* codigo, char modo, int qtd, float valor, int mes);
float getFaturacaoNormal(Contab c, char* codigo, int mes);
float getFaturacaoPromo(Contab c, char* codigo, int mes);
int getVendasNormal(Contab c, char* codigo, int mes);
int getVendasPromo(Contab c, char* codigo, int mes);
int getNVendasNormal(Contab c, char* codigo, int mes);
int getNVendasPromo(Contab c, char* codigo, int mes);
typedef struct arvoreContabil* CTree;
void insert(CTree ct, char* codigo);
CTree new();
void dispose(CTree nodo);
void insereCompra(CTree ct, char* codigo, char modo, int qtd, float valor, int mes);
float getFaturacaoNormal(CTree ct, char* codigo, int mes);
float getFaturacaoPromo(CTree ct, char* codigo, int mes);
int getVendasNormal(CTree ct, char* codigo, int mes);
int getVendasPromo(CTree ct, char* codigo, int mes);
int getNVendasNormal(CTree ct, char* codigo, int mes);
int getNVendasPromo(CTree ct, char* codigo, int mes);
#endif

