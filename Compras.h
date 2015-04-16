/* 
 * File:   Compras.h
 * Author: Pedro Cunha
 *
 * Created on 6 de Março de 2015, 16:56
 */

#ifndef COMPRAS_H
#define	COMPRAS_H
#include "EstruturasAux.h"
#include "CusTypes.h"


typedef struct compra* Compra;
/**
 * Criação de um novo registo de compra
 * @param codigoP Código de Produto
 * @param valorUni Valor Unitário
 * @param quantidade Quantidade comprada
 * @param modo Modo(N)ormal ou (P)romoção
 * @param codigoC Código de Cliente 
 * @param mes Mês
 * @return Nova compra
 */
Compra new(Codigo codigoP, float valorUni, int quantidade, char modo, Codigo codigoC, int mes);
/**
 * 
 * 
 * @return Código de Produto da Compra
 */
Codigo getCodigoP(Compra com);
/**
 * 
 * 
 * @return Valor unitário
 */
float getValorUni(Compra com);
/**
 * 
 * 
 * @return Quantidade Comprada
 */
int getQuantidade(Compra com);
/**
 * 
 * 
 * @return Modo da Compra
 */
char getModo(Compra com);
/**
 * 
 * 
 * @return Código de Cliente
 */
Codigo getCodigoC(Compra com);
/**
 * 
 * 
 * @return Mês da Compra
 */
int getMes(Compra com);
/**
 * Função de teste de igualdade entre duas compras
 * 
 * 
 * @return Igualdade entre Duas Compras
 */
int equals(Compra c1, Compra c2);

typedef struct compratree* CompraTree;
/**
 * Inicialiação da árvore de compras
 * @return Árvore de compras inicializada
 */
CompraTree new();
/**
 * Inserção de compra
 */
CompraTree insert(CompraTree ct, Compra c);
/**
 * Inserção de compra
 */
CompraTree insert(CompraTree ct, Codigo codigoP, float valorUni, int quantidade, char modo, Codigo codigoC, int mes);
/**
 * Funcao utilizada para atualizar a árvore de produtos ao efectuar-se uma compra
 * @param pt Árvore de produtos
 * @param codigoP Código de Produto
 * @param qtd Quantidade
 * @param valor Valor unitário
 * @param modo Modo de compra
 * @param codigoC Código de Cliente
 * @param mes Mês
 */
ProdutoTree updateProdTree(ProdutoTree pt, Codigo codigoP, int qtd, float valor, char modo, Codigo codigoC, int mes);
/**
 * Funcao utilizada para atualizar a árvore de clientes ao efectuar-se uma compra
 * @param ct Árvore de produtos
 * @param codigoP Código de Produto
 * @param qtd Quantidade
 * @param valor Valor unitário
 * @param modo Modo de compra
 * @param codigoC Código de Cliente
 * @param mes Mês
 */
ClienteTree updateCliTree(ClienteTree ct, Codigo codigoP, int qtd, float valor, char modo, Codigo codigoC, int mes);

typedef struct produto* Produto;
/**
 * Inicialização do Produto
 * @param codigo Código de Produto
 * @return Produto inicializado com o código indicado por codigo
 */
Produto new(Codigo codigo);
/**
 * 
 * 
 * @return Código de Produto
 */
Codigo getCodigo(Produto p);
/**
 * 
 * 
 * @return Número de vezes que o Produto p foi comprado
 */
int getNVezesComprado(Produto p);
/**
 * 
 * 
 * @return Array de códigos dos clientes compradores 
 */
CodigoArray getCliCompradores(Produto p);
/**
 * 
 * @param p Produto a ser consultado
 * @param mes Mês a ser consultado
 * @return Número de vezes que o produto foi comprado no mês
 */
int getVezesComprado(Produto p, int mes);
/**
 * 
 * @return 1 se o produto foi comprado em todos os meses do ano, 0 caso contrário
 */
int compradoEmTodosOsMeses(Produto p);

typedef struct cliente* Cliente;
/**
 * Inicialização de um cliente
 * @param codigo Código de Cliente
 * @return Cliente Inicializado com o código indicado por codigo
 */
Cliente new(Codigo codigo);
/**
 * 
 * @return Código de Cliente
 */
Codigo getCodigo(Cliente c);
/**
 * 
 * 
 * @return Número de Compras de um cliente
 */
int getNCompras(Cliente c);
/**
 * 
 * 
 * @return Array com os códigos de Produtos comprados pelo cliente
 */
CodigoArray getProdComprados(Cliente c);
/**
 * 
 * @param c Cliente a ser consultado
 * @param mes Mês a ser consultado
 * @return Número de compras realizadas pelo cliente no mês em questão
 */
int getCompras(Cliente c, int mes);
/**
 * 
 * @return 1 se o cliente comprou em todos os meses do ano, 0 caso contrário
 */
int compraEmTodosOsMeses(Cliente c);
Boolean compradoMes(Produto p,int mes);
Boolean compraNoMes(Cliente c,int mes);
/*Árvore de Produtos*/
typedef struct produtoTree* ProdutoTree;
ProdutoTree new();
ProdutoTree insert(ProdutoTree pt, Produto p);
ProdutoTree insert(ProdutoTree pt, Codigo codigoP);
/*Árvore de Clientes*/
typedef struct clienteTree* ClienteTree;
ClienteTree new();
ClienteTree insert(ClienteTree ct, Cliente c);
ClienteTree insert(ClienteTree ct, Codigo codigoC);
void dispose(ClienteTree ct);
void dispose(CompraTree ct);
void dispose(ProdutoTree pt);
CodigoArray nuncaComprados(ComprasDB cdb);
/*Camada de Convergência*/
typedef struct comprasDB* ComprasDB;
ComprasDB new();
ComprasDB insertCliente(ComprasDB cdb, Codigo codigoC);
ComprasDB insertProduto(ComprasDB cdb, Codigo codigoP);
ComprasDB registerSale(ComprasDB cdb, Codigo codigoP, float valor, int qtd, char modo, Codigo codigoC, int mes);
void dispose(ComprasDB cdb);
TabelaCSV carregaCliente(TabelaCSV csv,Cliente cli);
/*
 * Métodos auxiliares À resolução das queries
 */

Par procuraNaoUtilizados(ComprasDB cdb);
Table getTabelaCompras(ComprasDB cdb, Codigo codigo);
ListaDePCM clientesCompradores(ComprasDB cdb, Codigo codigo) ;
CodigoArray getTopComprasMensal(ComprasDB cdb,Codigo codigo,int mes);
CodigoArray compraTodos(ComprasDB cdb);
ArvoreQtd produtosToQtdArvore(ComprasDB cdb);
CodigoArray getTopCompras(ComprasDB cdb,Codigo codigo);
#endif

