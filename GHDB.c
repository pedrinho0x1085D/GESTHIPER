
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

void insertProd(GHDB db, Codigo codigo) {
    insert(db->produtos, codigo);
    insertProduto(db->compras, codigo);
    insert(db->contabilidade, codigo);
}

void insertCli(GHDB db, Codigo codigo) {
    insert(db->clientes, codigo);
    insertCliente(db->compras, codigo);
}

void insertComp(GHDB db, Codigo codigoP, float valor, int qtd, char modo, Codigo codigoC, int mes) {
    registerSale(db->compras, codigoP, valor, qtd, modo, codigoC, mes);
    insereCompra(db->contabilidade, codigoP, modo, qtd, valor, mes);
}

CodigoArray getClientes(GHDB db, Codigo primeira_letra) {
    return getTreeToArray(db->clientes, primeira_letra);
}

CodigoArray getProdutos(GHDB db, Codigo primeira_letra) {
    return getTreeToArray(db->produtos, primeira_letra);
}

AuxR2 getContabilidadeProduto(GHDB db, Codigo produto, int mes) {
    return getDadosProduto(db->contabilidade, produto, mes);
}

CodigoArray getProdutosNuncaComprados(GHDB db) {
    return nuncaComprados(db->compras);
}

Table getTabelaProdutos(GHDB db, Codigo codigo) {
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
CodigoArray getTopCompras(GHDB db, Codigo codigo){
    int i;
    CodigoArray ca=getTopCompras(db->compras,codigo);
    return getFirstN(ca,3);
}
CodigoArray getTopComprasMensal(GHDB db, Codigo codigo, int mes){
    return getTopComprasMensal(db->compras,codigo,mes);
}
/*CodigoArray getClientesCompradores(GHDB db,Codigo codigo){
    return clientesCompradores(db->compras,codigo);
}
CodigoArray getNMaisVendidos(GHDB db, int n){
    CodigoArray ca=getCodigosDecresc(ProdutosToQtdArvore(db->compras));
    return getFirstN(ca,n);
}*/
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

int prodCodeNotExistent(GHDB db, Codigo codigoP) {
    return !(searchCode(db->produtos, codigoP));
}

int cliCodeNotExistent(GHDB db, Codigo codigoC) {
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