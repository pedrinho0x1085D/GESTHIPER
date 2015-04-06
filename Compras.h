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
Compra new(char* codigoP, float valorUni, int quantidade, char modo, char* codigoC, int mes);
/**
 * 
 * 
 * @return Código de Produto da Compra
 */
char* getCodigoP(Compra com);
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
char* getCodigoC(Compra com);
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
void insert(CompraTree ct, char* codigoP, float valorUni, int quantidade, char modo, char* codigoC, int mes);
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
void updateProdTree(ProdutoTree pt, char* codigoP, int qtd, float valor, char modo, char* codigoC, int mes);
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
void updateCliTree(ClienteTree ct, char* codigoP, int qtd, float valor, char modo, char* codigoC, int mes);

typedef struct produto* Produto;
/**
 * Inicialização do Produto
 * @param codigo Código de Produto
 * @return Produto inicializado com o código indicado por codigo
 */
Produto new(char* codigo);
/**
 * 
 * 
 * @return Código de Produto
 */
char* getCodigo(Produto p);
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
char* getCodigo(Cliente c);
int getNCompras(Produto p);
CodigoArray getProdComprados(Produto p);
int getCompras(Cliente c, int mes);
int compraEmTodosOsMeses(Cliente c);

typedef struct produtoTree* ProdutoTree;
ProdutoTree new();
void insert(ProdutoTree pt, Produto p);
void insert(ProdutoTree pt, char* codigoP);

typedef struct clienteTree* ClienteTree;
ClienteTree new();
void insert(ClienteTree ct, Cliente c);
void insert(ClienteTree ct, char* codigoC);
void dispose(ClienteTree ct);
void dispose(CompraTree ct);
void dispose(ProdutoTree pt);
CodigoArray nuncaComprados(ComprasDB cdb);

typedef struct comprasDB* ComprasDB;
ComprasDB new();
void insertCliente(ComprasDB cdb, char* codigoC);
void insertProduto(ComprasDB cdb, char* codigoP);
void registerSale(ComprasDB cdb, char* codigoP, float valor, int qtd, char modo, char* codigoC, int mes);
void dispose(ComprasDB cdb);

typedef struct tabela* Table;
Table new(char* codigo);
void addValor(Table t, int qtd, int mes);
char* getCodigo(Table t);
int getCompras(Table t, int mes);
void dispose(Table t);
void toTxtFile(Table t,char* filename);
Table getTabelaCompras(ComprasDB dbc,char* codigo);
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
TreeTop newNode(char* codigo,int totalQtd);
void insertNode(TreeTop arvore, char*codigo,int totalQtd);
TreeTop clienteToTreeTop(Cliente cl);
CodigoArray topCompras(TreeTop aux);
CodigoArray getTopComprasMensal(ComprasDB cdb, char* codigo, int mes);
TreeTop constroiTopComprasMensal(Cliente cl, int mes);

typedef struct arvoreQ8* ArvoreClientes;
ArvoreClientes new();
ArvoreClientes newNode();
void insert(ArvoreClientes ac, char* codigo, char modo);
CodigoArray clientesCompradores(ComprasDB cdb, char* codigoP);
int contaClientesDif(ArvoreClientes ac);
ArvoreClientes produtoToArvoreCl(Produto p);
void dispose(ArvoreClientes ac);
char* nodeToString(ArvoreClientes node);

typedef struct treeQ12* ArvoreQtd;
ArvoreQtd new();
ArvoreQtd new(char* codigo, int qtd);
void dispose(ArvoreQtd aq);
void insert(ArvoreQtd aq, char* codigo, int qtd);
ArvoreQtd ProdutosToQtdArvore(ComprasDB cdb);
CodigoArray getCodigosDecresc(ArvoreQtd aq);
char* nodeToString(ArvoreQtd node);
#endif

