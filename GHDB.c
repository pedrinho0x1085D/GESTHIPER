
#include "Catalog.h"
#include "GHDB.h"

struct db {
    int prodFileIsLoaded,cliFileIsLoaded,comFileIsLoaded, allFilesLoaded;
    Catalog produtos, clientes;
    /*Compras*/
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
}

void insertCli(GHDB db, char* codigo) {
    insert(db->clientes, codigo);
}

ArvoreAVL getClientes(GHDB db, char* primeira_letra) {
    return getTree(db->clientes, primeira_letra);
}

ArvoreAVL getProdutos(GHDB db, char* primeira_letra) {
    return getTree(db->produtos, primeira_letra);
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