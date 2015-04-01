
#include "Catalog.h"
#include "GHDB.h"
#include "Compras.h"

struct db {
    int prodFileIsLoaded,cliFileIsLoaded,comFileIsLoaded, allFilesLoaded;
    Catalog produtos, clientes;
    ComprasDB compras;
    /*Contabilidade*/
};

GHDB new() {
    GHDB aux = malloc(sizeof (struct db));
    aux->clientes = new();
    aux->produtos = new();
    aux->prodFileIsLoaded=0;
    aux->comFileIsLoaded=0;
    aux->cliFileIsLoaded=0;
    aux->allFilesLoaded=0;
    return aux;
}

void insertProd(GHDB db, char* codigo) {
    insert(db->produtos, codigo);
    insertProduto(db->compras);
}

void insertCli(GHDB db, char* codigo) {
    insert(db->clientes, codigo);
    insertCliente(db->compras,codigo);
}
void insertComp(GHDB db,char* codigoP,float valor,int qtd,char modo,char* codigoC,int mes){
    registerSale(db->compras,codigoP,valor,qtd,modo,codigoC,mes);
}

CodigoArray getClientes(GHDB db, char* primeira_letra) {
    return getTreeToArray(db->clientes, primeira_letra);
}

CodigoArray getProdutos(GHDB db, char* primeira_letra) {
    return getTreeToArray(db->produtos, primeira_letra);
}

int prodFileIsLoaded(GHDB db){
    return db->prodFileIsLoaded;
}

int cliFileIsLoaded(GHDB db){
    return db->cliFileIsLoaded;
}

int comFileIsLoaded(GHDB db){
    return db->comFileIsLoaded;
}

int allFilesLoaded(GHDB db){
    return db->allFilesLoaded;
}

void loadProdFile(GHDB db){
    db->prodFileIsLoaded=1;
    if(db->prodFileIsLoaded&&db->cliFileIsLoaded&&db->comFileIsLoaded) db->allFilesLoaded=1;
}

void loadCliFile(GHDB db){
    db->cliFileIsLoaded=1;
    if(db->prodFileIsLoaded&&db->cliFileIsLoaded&&db->comFileIsLoaded) db->allFilesLoaded=1;
}

void loadComFile(GHDB db){
    db->comFileIsLoaded=1;
    if(db->prodFileIsLoaded&&db->cliFileIsLoaded&&db->comFileIsLoaded) db->allFilesLoaded=1;
}

int prodCodeNotExistent(GHDB db,char* codigoP){
    return !(searchCode(db->produtos,codigoP));
}

int cliCodeNotExistent(GHDB db,char* codigoC){
    return !(searchCode(db->clientes,codigoC));
}