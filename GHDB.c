
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

GHDB new() {
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

GHDB insertProd(GHDB db, Codigo codigo) {
    GHDB aux=db;
    aux->produtos=insert(aux->produtos, codigo);
    aux->compras=insertProduto(aux->compras, codigo);
    aux->contabilidade=insert(aux->contabilidade, codigo);
    return aux;
}

GHDB insertCli(GHDB db, Codigo codigo) {
    GHDB aux=db;
    aux->clientes=insert(aux->clientes, codigo);
    aux->compras=insertCliente(aux->compras, codigo);
    return aux;
}

GHDB insertComp(GHDB db, Codigo codigoP, float valor, int qtd, char modo, Codigo codigoC, int mes) {
    GHDB aux=db;
    aux->compras=registerSale(aux->compras, codigoP, valor, qtd, modo, codigoC, mes);
    aux->contabilidade=insereCompra(aux->contabilidade, codigoP, modo, qtd, valor, mes);
    return aux;
}

CodigoArray getClientes(GHDB db, Codigo primeira_letra) {
    return getTreeToArray(db->clientes, primeira_letra);
}

CodigoArray getProdutos(GHDB db, Codigo primeira_letra) {
    return getTreeToArray(db->produtos, primeira_letra);
}

VendasProduto getContabilidadeProduto(GHDB db, Codigo produto, int mes) {
    return getDadosProduto(db->contabilidade, produto, mes);
}

CodigoArray getProdutosNuncaComprados(GHDB db) {
    return nuncaComprados(db->compras);
}

/*Table getTabelaProdutos(GHDB db, Codigo codigo) {
    return getTabelaCompras(db->compras, codigo);
}*/

TabelaCSV getRelacao(GHDB db) {
    TabelaCSV aux=new();
    aux=carregaCompras(db->contabilidade,aux);
    aux=carregaClientes(db->compras,aux);
    return aux;
}

Par procuraNaoUtilizados(GHDB db) {
    return procuraNaoUtilizados(db->compras);
}

Faturacao criaLista(GHDB db, int lower, int higher) {
    return criaLista(db->contabilidade, lower, higher);
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
Boolean prodFileIsLoaded(GHDB db) {
    return db->prodFileIsLoaded;
}

Boolean cliFileIsLoaded(GHDB db) {
    return db->cliFileIsLoaded;
}

Boolean comFileIsLoaded(GHDB db) {
    return db->comFileIsLoaded;
}

Boolean allFilesLoaded(GHDB db) {
    return db->allFilesLoaded;
}

void loadProdFile(GHDB db) {
    db->prodFileIsLoaded = TRUE;
    if (db->prodFileIsLoaded && db->cliFileIsLoaded && db->comFileIsLoaded) db->allFilesLoaded = TRUE;
}

void loadCliFile(GHDB db) {
    db->cliFileIsLoaded = TRUE;
    if (db->prodFileIsLoaded && db->cliFileIsLoaded && db->comFileIsLoaded) db->allFilesLoaded = TRUE;
}

void loadComFile(GHDB db) {
    db->comFileIsLoaded = TRUE;
    if (db->prodFileIsLoaded && db->cliFileIsLoaded && db->comFileIsLoaded) db->allFilesLoaded = TRUE;
}

Boolean prodCodeNotExistent(GHDB db, Codigo codigoP) {
    return !(searchCode(db->produtos, codigoP));
}

Boolean cliCodeNotExistent(GHDB db, Codigo codigoC) {
    return !(searchCode(db->clientes, codigoC));
}

void disposeReload(GHDB db) {
    db->allFilesLoaded=FALSE;
    dispose(db->clientes);
    db->cliFileIsLoaded=FALSE;
    db->clientes = new();
    dispose(db->produtos);
    db->prodFileIsLoaded=FALSE;
    db->produtos = new();
    dispose(db->compras);
    db->comFileIsLoaded=FALSE;
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