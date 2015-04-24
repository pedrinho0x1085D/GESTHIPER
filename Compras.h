/*
 *        __      __   ______
 *       / /     / /  |____  \
 *      / /     / /     ___| |
 *     / /     / /     |___  |
 *    / /___  / /      ____| |
 *   /_____/ /_/      |______/
 *
 *
 *  Ficheiro: Compras.h
 *
 */

#ifndef COMPRAS_H
#define	COMPRAS_H
#include "EstruturasAux.h"
#include "CusTypes.h"


typedef struct compra* Compra;
typedef struct compratree* CompraTree;
typedef struct cliente* Cliente;
typedef struct produtoTree* ProdutoTree;
typedef struct clienteTree* ClienteTree;
typedef struct comprasDB* ComprasDB;
typedef struct produto* Produto;

struct simpleProd* newSP(Codigo codigo, int mes);
struct simpleCli* newSC(Codigo codigo, int mes);
struct simpleCli* sc_update(struct simpleCli* sc, int qtd, float valor, char modo, Codigo codigoC, int mes);
struct simpleProd* sp_update(struct simpleProd* sp, int qtd, float valor, char modo, Codigo codigoP, int mes);
Par procuraNaoCompra(ClienteTree ct, Par p);
Par procuraNaoComprado(ProdutoTree pt, Par p);
Table CDB_aux_carregaCompras(Table t, struct simpleProd* sp);
ArvoreClientes CDB_carregaClientes(ArvoreClientes ac, struct simpleCli* sc); 
TreeTop CDB_constroiTop(struct simpleProd* sp, TreeTop tt, int mes);
TreeTop constroiTopCompras(struct simpleProd* sp,TreeTop tt,CodigoArray ca);
CodigoArray compradoresTraversal(struct simpleCli* comps, CodigoArray ca);
CodigoArray produtosTraversal(struct simpleProd* comps, CodigoArray ca);
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
Compra newComp(Codigo codigoP, float valorUni, int quantidade, char modo, Codigo codigoC, int mes);
/**
 * 
 * 
 * @return Código de Produto da Compra
 */
Codigo Comp_getCodigoP(Compra com);
/**
 * 
 * 
 * @return Valor unitário
 */
float Comp_getValorUni(Compra com);
/**
 * 
 * 
 * @return Quantidade Comprada
 */
int Comp_getQuantidade(Compra com);
/**
 * 
 * 
 * @return Modo da Compra
 */
char Comp_getModo(Compra com);
/**
 * 
 * 
 * @return Código de Cliente
 */
Codigo Comp_getCodigoC(Compra com);
/**
 * 
 * 
 * @return Mês da Compra
 */
int Comp_getMes(Compra com);
/**
 * Função de teste de igualdade entre duas compras
 * 
 * 
 * @return Igualdade entre Duas Compras
 */
int Comp_equals(Compra c1, Compra c2);


/**
 * Inicialiação da árvore de compras
 * @return Árvore de compras inicializada
 */
CompraTree newCompT();
/**
 * Inserção de compra
 */
CompraTree CompT_insertC(CompraTree ct, Compra c);
/**
 * Inserção de compra
 */
CompraTree CompT_insert(CompraTree ct, Codigo codigoP, float valorUni, int quantidade, char modo, Codigo codigoC, int mes);
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
ProdutoTree ProdT_updateProdTree(ProdutoTree pt, Codigo codigoP, int qtd, float valor, char modo, Codigo codigoC, int mes);
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
ClienteTree ClienT_updateCliTree(ClienteTree ct, Codigo codigoP, int qtd, float valor, char modo, Codigo codigoC, int mes);

/**
 * Inicialização do Produto
 * @param codigo Código de Produto
 * @return Produto inicializado com o código indicado por codigo
 */
Produto newProd(Codigo codigo);
/**
 * 
 * 
 * @return Código de Produto
 */
Codigo Prod_getCodigo(Produto p);
/**
 * 
 * 
 * @return Número de vezes que o Produto p foi comprado
 */
int Prod_getNVezesComprado(Produto p);
/**
 * 
 * 
 * @return Array de códigos dos clientes compradores 
 */
CodigoArray Prod_getCliCompradores(Produto p);
/**
 * 
 * @param p Produto a ser consultado
 * @param mes Mês a ser consultado
 * @return Número de vezes que o produto foi comprado no mês
 */
int Prod_getVezesComprado(Produto p, int mes);
/**
 * 
 * @return 1 se o produto foi comprado em todos os meses do ano, 0 caso contrário
 */
int Prod_compradoEmTodosOsMeses(Produto p);
int Prod_getQuantidadeComprada(Produto p);
/**
 * Inicialização de um cliente
 * @param codigo Código de Cliente
 * @return Cliente Inicializado com o código indicado por codigo
 */
Cliente newCli(Codigo codigo);
/**
 * 
 * @return Código de Cliente
 */
Codigo Cli_getCodigo(Cliente c);
/**
 * 
 * 
 * @return Número de Compras de um cliente
 */
int Cli_getNCompras(Cliente c);
/**
 * 
 * 
 * @return Array com os códigos de Produtos comprados pelo cliente
 */
CodigoArray Cli_getProdComprados(Cliente c);
/**
 * 
 * @param c Cliente a ser consultado
 * @param mes Mês a ser consultado
 * @return Número de compras realizadas pelo cliente no mês em questão
 */
int Cli_getCompras(Cliente c, int mes);
/**
 * 
 * @return 1 se o cliente comprou em todos os meses do ano, 0 caso contrário
 */
int Cli_compraEmTodosOsMeses(Cliente c);
Boolean Prod_compradoMes(Produto p,int mes);
Boolean Cli_compraNoMes(Cliente c,int mes);
/*Árvore de Produtos*/

ProdutoTree newProdT();
ProdutoTree ProdT_insertP(ProdutoTree pt, Produto p);
ProdutoTree ProdT_insert(ProdutoTree pt, Codigo codigoP);
/*Árvore de Clientes*/

ClienteTree newClienT();
ClienteTree ClienT_insertC(ClienteTree ct, Cliente c);
ClienteTree ClienT_insert(ClienteTree ct, Codigo codigoC);
void ClienT_dispose(ClienteTree ct);
void CompT_dispose(CompraTree ct);
void ProdT_dispose(ProdutoTree pt);

/*Camada de Convergência*/

ComprasDB newCDB();
ComprasDB CDB_insertCliente(ComprasDB cdb, Codigo codigoC);
ComprasDB CDB_insertProduto(ComprasDB cdb, Codigo codigoP);
ComprasDB CDB_registerSale(ComprasDB cdb, Codigo codigoP, float valor, int qtd, char modo, Codigo codigoC, int mes);
void CDB_dispose(ComprasDB cdb);
TabelaCSV CDB_carregaClienteCSV(TabelaCSV csv,Cliente cli);
/*
 * Métodos auxiliares À resolução das queries
 */

Par CDB_procuraNaoUtilizados(ComprasDB cdb);
Table CDB_getTabelaCompras(ComprasDB cdb, Codigo codigo);
ListaDePCM CDB_clientesCompradores(ComprasDB cdb, Codigo codigo) ;
CodigoArray CDB_getTopComprasMensal(ComprasDB cdb,Codigo codigo,int mes);
CodigoArray CDB_compraTodos(ComprasDB cdb);
ArvoreQtd CDB_produtosToQtdArvore(ComprasDB cdb);
CodigoArray CDB_getTopCompras(ComprasDB cdb,Codigo codigo);
TabelaCSV CDB_carregaClientesCSV(ComprasDB cdb, TabelaCSV csv);


#endif

