/* 
 * File:   Compras.h
 * Author: Pedro Cunha
 *
 * Created on 6 de Março de 2015, 16:56
 */

#ifndef COMPRAS_H
#define	COMPRAS_H
#include "Codigo.h"

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
void insert(CompraTree ct, Compra c);
/**
 * Inserção de compra
 */
void insert(CompraTree ct, Codigo codigoP, float valorUni, int quantidade, char modo, Codigo codigoC, int mes);
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
void updateProdTree(ProdutoTree pt, Codigo codigoP, int qtd, float valor, char modo, Codigo codigoC, int mes);
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
void updateCliTree(ClienteTree ct, Codigo codigoP, int qtd, float valor, char modo, Codigo codigoC, int mes);

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
/*Árvore de Produtos*/
typedef struct produtoTree* ProdutoTree;
ProdutoTree new();
void insert(ProdutoTree pt, Produto p);
void insert(ProdutoTree pt, Codigo codigoP);
/*Árvore de Clientes*/
typedef struct clienteTree* ClienteTree;
ClienteTree new();
void insert(ClienteTree ct, Cliente c);
void insert(ClienteTree ct, Codigo codigoC);
void dispose(ClienteTree ct);
void dispose(CompraTree ct);
void dispose(ProdutoTree pt);
CodigoArray nuncaComprados(ComprasDB cdb);
/*Camada de Convergência*/
typedef struct comprasDB* ComprasDB;
ComprasDB new();
void insertCliente(ComprasDB cdb, Codigo codigoC);
void insertProduto(ComprasDB cdb, Codigo codigoP);
void registerSale(ComprasDB cdb, Codigo codigoP, float valor, int qtd, char modo, Codigo codigoC, int mes);
void dispose(ComprasDB cdb);
/*
 * Estruturas e métodos auxiliares À resolução das queries
 */
typedef struct tabela* Table;
Table new(Codigo codigo);
void addValor(Table t, int qtd, int mes);
Codigo getCodigo(Table t);
int getCompras(Table t, int mes);
void dispose(Table t);
void toTxtFile(Table t,char* filename);
Table getTabelaCompras(ComprasDB dbc,Codigo codigo);
void constroiTabela(Cliente cli, Table tab);

typedef struct tableQ11* TabelaCSV;
TabelaCSV new();
void add(TabelaCSV tcsv, int mes, int qtd);
void dispose(TabelaCSV tcsv);
TabelaCSV getRelacao(ComprasDB cdb);
void toCsvFile(TabelaCSV csv,char* filename);

typedef struct par* Par;
Par new();
Par dispose(Par p);
void addCliente(Par p);
void addProduto(Par p);
int getClientesSemCompras(Par p);
int getProdutosNaoComprados(Par p);
Par procuraNaoUtilizados(ComprasDB dbc);

int in(int x,int linf,int lsup);

typedef struct auxilQ7* AuxQ7;
AuxQ7 new();
void dispose(AuxQ7 aux);
float getFaturacao(AuxQ7 aux);
int getNCompras(AuxQ7 aux);
void insereCompra(AuxQ7 auxil, float valor,int qtd);
AuxQ7 criaLista(ComprasDB cdb, int lower,int higher);

CodigoArray compraTodos(ComprasDB cdb);

typedef struct nodeTop* TreeTop;
TreeTop newNode(Codigo codigo,int totalQtd);
void insertNode(TreeTop arvore, Codigo codigo,int totalQtd);
TreeTop clienteToTreeTop(Cliente cl);
CodigoArray topCompras(TreeTop aux);
CodigoArray getTopComprasMensal(ComprasDB cdb, Codigo codigo, int mes);
TreeTop constroiTopComprasMensal(Cliente cl, int mes);

typedef struct arvoreQ8* ArvoreClientes;
ArvoreClientes new();
ArvoreClientes newNode();
void insert(ArvoreClientes ac, Codigo codigo, char modo);
CodigoArray clientesCompradores(ComprasDB cdb, Codigo codigoP);
int contaClientesDif(ArvoreClientes ac);
ArvoreClientes produtoToArvoreCl(Produto p);
void dispose(ArvoreClientes ac);


typedef struct treeQ12* ArvoreQtd;
ArvoreQtd new();
ArvoreQtd new(Codigo codigo, int qtd);
void dispose(ArvoreQtd aq);
void insert(ArvoreQtd aq, Codigo codigo, int qtd);
ArvoreQtd ProdutosToQtdArvore(ComprasDB cdb);
CodigoArray getCodigosDecresc(ArvoreQtd aq);

typedef struct parCodModo* ParCodigoModo;
ParCodigoModo new(Codigo codigo, char modo);
Codigo getCodigo(ParCodigoModo pcm);
char getModo(ParCodigoModo pcm);

typedef struct parCodQtd* ParCodigoQtd;
ParCodigoQtd new(Codigo codigo, int qtd);
Codigo getCodigo(ParCodigoQtd pcq);
int getQtd(ParCodigoQtd pcq);

#endif

