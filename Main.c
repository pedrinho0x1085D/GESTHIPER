#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GHDB.h"

void leituraCli(GHDB db, char* filename) {
    /*if(clFileIsLoaded(db) dispose(db);*/
    int nLinhas = 0;
    char linha[10];
    char *tok;
    FILE* file = fopen(filename, "r");
    while (fgets(file, linha, 10)!=NULL) {
        tok = strtok(linha, "\r\n");
        insertCli(db,tok);
        nLinhas++;
    }
    printf("Nome do ficheiro: %s\n%d Linhas lidas\n", filename, nLinhas);
}

void leituraProd(GHDB db,char* filename) {
    /*if(prodFileIsLoaded(db) dispose(db);*/
    int nLinhas = 0;
    char linha[10];
    char *tok;
    FILE* file = fopen(filename, "r");
    while (fgets(file, linha, 10)!=NULL) {
        tok = strtok(linha, "\r\n");
        insertProd(db,tok);
        nLinhas++;
    }
    printf("Nome do ficheiro: %s\n%d Linhas lidas\n", filename, nLinhas);
}

void leituraComp(/*GHDB db, */char* filename) {
    FILE* file = fopen(filename, "r");
    int nLinhas = 0, linhasMal = 0;
    char linha[1024];
    char *codigoP, *codigoC;
    float valor;
    int qtd, mes;
    char *modoaux,modo;
    
    int flag = 0;

    /**	if(comFileIsLoaded(db)){
    dispose(db);         
    db=new();
            }*/

    while (fgets(file, linha, 10) != NULL) {
        flag = 0;
        codigoP = strtok(linha, " ");
        /*if(prodCodeNotExistent(db,codigoP)) {linhasMal++; flag =1;}*/
        valor = atof(strtok(NULL, " "));
        if (valor < 0&&flag==0) {
            linhasMal++;
            flag = 1;
        }
        qtd = atoi(strtok(NULL, " "));
        if (qtd < 0&&flag==0) {
            linhasMal++;
            flag = 1;
        }
        modoaux = strtok(NULL, " ");
        modo=modoaux[0];
        codigoC = strtok(NULL, " ");
        /*if(cliCodeNotExistent(db,codigoP)&&flag==0) {linhasMal++; flag =1;}*/
        mes = atoi(strtok(NULL, " "));
        if (mes < 1 || mes > 12&&flag==0) {
            linhasMal++;
            flag = 1;
        }
        nLinhas++;
        if(!flag) insertComp(db,codigoP,valor,qtd,modo,codigoC,mes);
    }
    printf("Nome do ficheiro: %s\nNumero de Linhas Lidas: %d, das quais: \n%d linhas mal formatadas, %d linhas validadas",filename, nLinhas, linhasMal, nLinhas - linhasMal);
}

