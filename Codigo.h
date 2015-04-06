/* 
 * File:   Codigo.h
 * Author: iFilipe
 *
 * Created on 11 de Março de 2015, 15:23
 */

#ifndef CODIGO_H
#define	CODIGO_H

typedef char* Codigo;
typedef Codigo* CodigoArray;
CodigoArray new();
int getSize(CodigoArray ca);
void insert(CodigoArray ca, Codigo co);
void dispose(CodigoArray ca);
int in(Codigo co, CodigoArray ca);
CodigoArray getFirstN(CodigoArray ca, int n);
int min(int x1,int x2);
#endif	/* CODIGO_H */

