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









typedef struct cliente* Cliente;



typedef struct comprasDB* ComprasDB;



typedef struct produto* Produto;









Produto ProdT_updateProd(Produto pt, Codigo codigoP, int qtd, float valor, char modo, Codigo codigoC, int mes);



Cliente ClienT_updateCli(Cliente ct, Codigo codigoP, int qtd, float valor, char modo, Codigo codigoC, int mes);





Produto newProd(Codigo codigo);



Codigo Prod_getCodigo(Produto p);



int Prod_getNVezesComprado(Produto p);



CodigoArray Prod_getCliCompradores(Produto p);



int Prod_getVezesComprado(Produto p, int mes);



int Prod_compradoEmTodosOsMeses(Produto p);

int Prod_getQuantidadeComprada(Produto p);



Cliente newCli(Codigo codigo);



Codigo Cli_getCodigo(Cliente c);



int Cli_getNCompras(Cliente c);



CodigoArray Cli_getProdComprados(Cliente c);



int Cli_getCompras(Cliente c, int mes);



int Cli_compraEmTodosOsMeses(Cliente c);

Boolean Prod_compradoMes(Produto p, int mes);

Boolean Cli_compraNoMes(Cliente c, int mes);

/*Árvore de Produtos*/



Produto newProdT();





Produto ProdT_insert(Produto pt, Codigo codigoP);

Produto Prod_getProduto(Produto p, Codigo codigoP);



Cliente newClienT();



Cliente ClienT_insert(Cliente ct, Codigo codigoC);

Cliente Cli_getCli(Cliente ct, Codigo codigoC);

void ClienT_dispose(Cliente ct);



void ProdT_dispose(Produto pt);



/*Camada de Convergência*/



ComprasDB newCDB();

ComprasDB CDB_insertCliente(ComprasDB cdb, Codigo codigoC);

ComprasDB CDB_insertProduto(ComprasDB cdb, Codigo codigoP);

ComprasDB CDB_registerSale(ComprasDB cdb, Codigo codigoP, float valor, int qtd, char modo, Codigo codigoC, int mes);

void CDB_dispose(ComprasDB cdb);

TabelaCSV CDB_carregaClienteCSV(Cliente cli, TabelaCSV csv);

/*

 * Métodos auxiliares À resolução das queries

 */



Par CDB_procuraNaoUtilizados(ComprasDB cdb);

Table CDB_getTabelaCompras(ComprasDB cdb, Codigo codigo);

ListaDePCM CDB_clientesCompradores(ComprasDB cdb, Codigo codigo);

CodigoArray CDB_getTopComprasMensal(ComprasDB cdb, Codigo codigo, int mes);

CodigoArray CDB_compraTodos(ComprasDB cdb);

ArvoreQtd CDB_produtosToQtdArvore(ComprasDB cdb);

CodigoArray CDB_getTopCompras(ComprasDB cdb, Codigo codigo);

TabelaCSV CDB_carregaClientesCSV(ComprasDB cdb, TabelaCSV csv);





#endif

