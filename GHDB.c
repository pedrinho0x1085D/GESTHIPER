
#include "Catalog.h"
#include "GHDB.h"
#include "Compras.h"
#include "Contabilidade.h"

struct db {
    int prodFileIsLoaded, cliFileIsLoaded, comFileIsLoaded, allFilesLoaded;
    Catalog produtos, clientes;
    ComprasDB compras;
    CTree contabilidade;
};

GHDB new() {
    GHDB aux = malloc(sizeof (struct db));
    aux->clientes = new();
    aux->produtos = new();
    aux->contabilidade = new();
    aux->compras = new();
    aux->prodFileIsLoaded = 0;
    aux->comFileIsLoaded = 0;
    aux->cliFileIsLoaded = 0;
    aux->allFilesLoaded = 0;
    return aux;
}

void insertProd(GHDB db, char* codigo) {
    insert(db->produtos, codigo);
    insertProduto(db->compras, codigo);
    insert(db->contabilidade, codigo);
}

void insertCli(GHDB db, char* codigo) {
    insert(db->clientes, codigo);
    insertCliente(db->compras, codigo);
}

void insertComp(GHDB db, char* codigoP, float valor, int qtd, char modo, char* codigoC, int mes) {
    registerSale(db->compras, codigoP, valor, qtd, modo, codigoC, mes);
    insereCompra(db->contabilidade, codigoP, modo, qtd, valor, mes);
}

CodigoArray getClientes(GHDB db, char* primeira_letra) {
    return getTreeToArray(db->clientes, primeira_letra);
}

CodigoArray getProdutos(GHDB db, char* primeira_letra) {
    return getTreeToArray(db->produtos, primeira_letra);
}

AuxR2 getContabilidadeProduto(GHDB db, char* produto, int mes) {
    return getDadosProduto(db->contabilidade, produto, mes);
}

CodigoArray getProdutosNuncaComprados(GHDB db) {
    return nuncaComprados(db->compras);
}

Table getTabelaProdutos(GHDB db, char* codigo) {
    return getTabelaCompras(db->compras, codigo);
}

TabelaCSV getRelacao(GHDB db) {
    return getRelacao(db->compras);
}

Par procuraNaoUtilizados(GHDB db) {
    return procuraNaoUtilizados(db->compras);
}

AuxQ7 criaLista(GHDB db, int lower, int higher) {
    return criaLista(db->compras, lower, higher);
}
CodigoArray getCompraEmTodosOsMeses(GHDB db){
    return compraTodos(db->compras);
}
CodigoArray getTopCompras(GHDB db, char* codigo){
    return getTopCompras(db->compras,codigo);
}
int prodFileIsLoaded(GHDB db) {
    return db->prodFileIsLoaded;
}

int cliFileIsLoaded(GHDB db) {
    return db->cliFileIsLoaded;
}

int comFileIsLoaded(GHDB db) {
    return db->comFileIsLoaded;
}

int allFilesLoaded(GHDB db) {
    return db->allFilesLoaded;
}

void loadProdFile(GHDB db) {
    db->prodFileIsLoaded = 1;
    if (db->prodFileIsLoaded && db->cliFileIsLoaded && db->comFileIsLoaded) db->allFilesLoaded = 1;
}

void loadCliFile(GHDB db) {
    db->cliFileIsLoaded = 1;
    if (db->prodFileIsLoaded && db->cliFileIsLoaded && db->comFileIsLoaded) db->allFilesLoaded = 1;
}

void loadComFile(GHDB db) {
    db->comFileIsLoaded = 1;
    if (db->prodFileIsLoaded && db->cliFileIsLoaded && db->comFileIsLoaded) db->allFilesLoaded = 1;
}

int prodCodeNotExistent(GHDB db, char* codigoP) {
    return !(searchCode(db->produtos, codigoP));
}

int cliCodeNotExistent(GHDB db, char* codigoC) {
    return !(searchCode(db->clientes, codigoC));
}

void disposeReload(GHDB db) {
    dispose(db->clientes);
    db->clientes = new();
    dispose(db->produtos);
    db->produtos = new();
    dispose(db->compras);
    db->compras = new();
    dispose(db->contabilidade);
    db->contabilidade = new();
}

void disposeExit(GHDB db) {
    dispose(db->clientes);
    dispose(db->produtos);
    dispose(db->compras);
    dispose(db->contabilidade);
    free(db);
}