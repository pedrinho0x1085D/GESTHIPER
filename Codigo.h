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
/**
 * Inicialização de um array de códigos
 * @return Array de Códigos 
 */
CodigoArray new();
/**
 * 
 * @param ca Array de Códigos a ser consultado
 * @return Tamanho do Array de Códigos
 */
int getSize(CodigoArray ca);
/**
 * Inserção de um Código num Array
 * @param ca Array de Códigos que vai receber o código
 * @param co Código a ser inserido
 */
void insert(CodigoArray ca, Codigo co);
/**
 * Libertação de espaço(Remoção do objecto)
 * @param ca Objecto a ser apagado
 */
void dispose(CodigoArray ca);
/**
 * Verifica se um Código encontra-se num Array de códigos
 * @param co Código a ser procurado
 * @param ca Array de códigos a ser consultado
 * @return 1 caso o código exista, 0 caso contrário
 */
int in(Codigo co, CodigoArray ca);
/**
 * Retorna um Array de códigos com os primeiros N elementos
 * @param ca Array de códigos a ser utilizado como base
 * @param n Número de elementos que o novo Array terá
 * @return Novo Array de Códigos com n elementos
 */
CodigoArray getFirstN(CodigoArray ca, int n);
/**
 * Retorna o mínimo entre dois inteiros
 * @return O mínimo entre dois inteiros
 */
int min(int x1,int x2);
/**
 * 
 * @param ca Array de códigos
 * @param i Posição
 * @return Código indexado na posição i.
 */
Codigo get(CodigoArray ca, int i);
#endif	/* CODIGO_H */

