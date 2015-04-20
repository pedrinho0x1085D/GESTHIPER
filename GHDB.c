
#include "Catalog.h"
#include "GHDB.h"
#include "Compras.h"
#include "Contabilidade.h"
#include "CusTypes.h"

struct db {
    Boolean prodFileIsLoaded, cliFileIsLoaded, comFileIsLoaded, allFilesLoaded;
    Catalog produtos, clientes;
    ComprasDB compras;
    CTree contabilidade;
};

GHDB newGHDB() {
    GHDB aux = malloc(sizeof (struct db));
    aux->clientes = new();
    aux->produtos = new();
    aux->contabilidade = new();
    aux->compras = new();
    aux->prodFileIsLoaded = FALSE;
    aux->comFileIsLoaded = FALSE;
    aux->cliFileIsLoaded = FALSE;
    aux->allFilesLoaded = FALSE;
    return aux;
}

GHDB GHDB_insertProd(GHDB db, Codigo codigo) {
    GHDB aux=db;
    aux->produtos=insert(aux->produtos, codigo);
    aux->compras=insertProduto(aux->compras, codigo);
    aux->contabilidade=insert(aux->contabilidade, codigo);
    return aux;
}

GHDB GHDB_insertCli(GHDB db, Codigo codigo) {
    GHDB aux=db;
    aux->clientes=insert(aux->clientes, codigo);
    aux->compras=insertCliente(aux->compras, codigo);
    return aux;
}

GHDB GHDB_insertComp(GHDB db, Codigo codigoP, float valor, int qtd, char modo, Codigo codigoC, int mes) {
    GHDB aux=db;
    aux->compras=registerSale(aux->compras, codigoP, valor, qtd, modo, codigoC, mes);
    aux->contabilidade=CT_insereCompra(aux->contabilidade, codigoP, modo, qtd, valor, mes);
    return aux;
}

CodigoArray GHDB_getClientes(GHDB db, Codigo primeira_letra) {
    return getTreeToArray(db->clientes, primeira_letra);
}

CodigoArray GHDB_getProdutos(GHDB db, Codigo primeira_letra) {
    return getTreeToArray(db->produtos, primeira_letra);
}

VendasProduto GHDB_getContabilidadeProduto(GHDB db, Codigo produto, int mes) {
    return CT_getDadosProduto(db->contabilidade, produto, mes);
}

CodigoArray GHDB_getProdutosNuncaComprados(GHDB db) {
    return nuncaComprados(db->compras);
}

Table GHDB_getTabelaProdutos(GHDB db, Codigo codigo) {
    return getTabelaCompras(db->compras, codigo);
}

TabelaCSV GHDB_getRelacao(GHDB db) {
    TabelaCSV aux=new();
    aux=CT_carregaCompras(db->contabilidade,aux);
    aux=carregaClientes(db->compras,aux);
    return aux;
}

Par GHDB_procuraNaoUtilizados(GHDB db) {
    return procuraNaoUtilizados(db->compras);
}

Faturacao GHDB_criaLista(GHDB db, int lower, int higher) {
    return criaLista(db->contabilidade, lower, higher);
}
CodigoArray GHDB_getCompraEmTodosOsMeses(GHDB db){
    return compraTodos(db->compras);
}
CodigoArray GHDB_getTopCompras(GHDB db, Codigo codigo){
    int i;
    CodigoArray ca=getTopCompras(db->compras,codigo);
    return CA_getFirstN(ca,3);
}
CodigoArray GHDB_getTopComprasMensal(GHDB db, Codigo codigo, int mes){
    return getTopComprasMensal(db->compras,codigo,mes);
}
ListaDePCM GHDB_getClientesCompradores(GHDB db,Codigo codigo){
    return clientesCompradores(db->compras,codigo);
}

CodigoArray GHDB_getNMaisVendidos(GHDB db, int n){
    CodigoArray ca=getCodigosDecresc(produtosToQtdArvore(db->compras),new());
    return CA_getFirstN(ca,n);
}
Boolean GHDB_prodFileIsLoaded(GHDB db) {
    return db->prodFileIsLoaded;
}

Boolean GHDB_cliFileIsLoaded(GHDB db) {
    return db->cliFileIsLoaded;
}

Boolean GHDB_comFileIsLoaded(GHDB db) {
    return db->comFileIsLoaded;
}

Boolean GHDB_allFilesLoaded(GHDB db) {
    return db->allFilesLoaded;
}

GHDB GHDB_loadProdFile(GHDB db) {
    GHDB aux=db;
    aux->prodFileIsLoaded = TRUE;
    if (aux->prodFileIsLoaded && aux->cliFileIsLoaded && aux->comFileIsLoaded) aux->allFilesLoaded = TRUE;
    return aux;
}

GHDB GHDB_loadCliFile(GHDB db) {
    GHDB aux=db;
    aux->cliFileIsLoaded = TRUE;
    if (aux->prodFileIsLoaded && aux->cliFileIsLoaded && aux->comFileIsLoaded) aux->allFilesLoaded = TRUE;
    return aux;
}

GHDB GHDB_loadComFile(GHDB db) {
    GHDB aux=db;
    aux->comFileIsLoaded = TRUE;
    if (aux->prodFileIsLoaded && aux->cliFileIsLoaded && aux->comFileIsLoaded) aux->allFilesLoaded = TRUE;
    return aux;
}

Boolean GHDB_prodCodeNotExistent(GHDB db, Codigo codigoP) {
    return !(searchCode(db->produtos, codigoP));
}

Boolean GHDB_cliCodeNotExistent(GHDB db, Codigo codigoC) {
    return !(searchCode(db->clientes, codigoC));
}

GHDB GHDB_disposeReload(GHDB db) {
    GHDB aux=db;
    aux->allFilesLoaded=FALSE;
    dispose(aux->clientes);
    aux->cliFileIsLoaded=FALSE;
    aux->clientes = new();
    dispose(aux->produtos);
    aux->prodFileIsLoaded=FALSE;
    aux->produtos = new();
    dispose(aux->compras);
    aux->comFileIsLoaded=FALSE;
    aux->compras = new();
    dispose(aux->contabilidade);
    aux->contabilidade = new();
    return aux;
}

void GHDB_disposeExit(GHDB db) {
    dispose(db->clientes);
    dispose(db->produtos);
    dispose(db->compras);
    dispose(db->contabilidade);
    free(db);
}