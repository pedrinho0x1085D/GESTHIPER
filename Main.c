#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GHDB.h"

/**
 * Método de Leitura de um ficheiro de clientes e posterior carregamento na Base de Dados
 * @param db Base de Dados que será carregada com os dados do ficheiro
 * @param filename Nome do Ficheiro que contém os códigos de cliente
 */
void leituraCli(GHDB db, char* filename) {
    if (cliFileIsLoaded(db)) disposeReload(db);
    int nLinhas = 0;
    char linha[10];
    char *tok;
    FILE* file = fopen(filename, "r");
    while (fgets(linha, 10, file) != NULL) {
        tok = strtok(linha, "\r\n");
        insertCli(db, tok);
        nLinhas++;
    }
    loadCliFile(db);
    printf("Nome do ficheiro: %s\n%d Linhas lidas\n", filename, nLinhas);
    fclose(file);
}

/**
 * Método de Leitura de um ficheiro de Produtos e posterior carregamento na Base de Dados
 * @param db Base de Dados que será carregada com os dados do ficheiro
 * @param filename Nome do Ficheiro que contém os códigos de produto
 */
void leituraProd(GHDB db, char* filename) {
    if (prodFileIsLoaded(db)) disposeReload(db);
    int nLinhas = 0;
    char linha[10];
    char *tok;
    FILE* file = fopen(filename, "r");
    while (fgets(linha, 10, file) != NULL) {
        tok = strtok(linha, "\r\n");
        insertProd(db, tok);
        nLinhas++;
    }
    loadProdFile(db);
    printf("Nome do ficheiro: %s\n%d Linhas lidas\n", filename, nLinhas);
    fclose(file);
}

/**
 * Método de Leitura de um ficheiro de Compras, validação dos dados existentes e posterior carregamento na Base de Dados
 * @param db Base de Dados que será carregada com os dados do ficheiro
 * @param filename Nome do Ficheiro que contém as informações de compra
 */
void leituraComp(GHDB db, char* filename) {
    FILE* file = fopen(filename, "r");
    int nLinhas = 0, linhasMal = 0;
    char linha[1024];
    char *codigoP, *codigoC;
    float valor;
    int qtd, mes;
    char *modoaux, modo;

    int flag = 0;

    if (comFileIsLoaded(db))
        disposeReload(db);

    while (fgets(linha, 30, file) != NULL) {
        flag = 0;
        codigoP = strtok(linha, " ");
        if (prodCodeNotExistent(db, codigoP)) {
            linhasMal++;
            flag = 1;
        }
        valor = atof(strtok(NULL, " "));
        if (valor < 0 && flag == 0) {
            linhasMal++;
            flag = 1;
        }
        qtd = atoi(strtok(NULL, " "));
        if (qtd < 0 && flag == 0) {
            linhasMal++;
            flag = 1;
        }
        modoaux = strtok(NULL, " ");
        modo = modoaux[0];
        codigoC = strtok(NULL, " ");
        if (cliCodeNotExistent(db, codigoP) && flag == 0) {
            linhasMal++;
            flag = 1;
        }
        mes = atoi(strtok(NULL, " "));
        if (mes < 1 || mes > 12 && flag == 0) {
            linhasMal++;
            flag = 1;
        }
        nLinhas++;
        if (!flag) insertComp(db, codigoP, valor, qtd, modo, codigoC, mes);
    }
    if (linhasMal != nLinhas) loadComFile(db);
    printf("Nome do ficheiro: %s\nNumero de Linhas Lidas: %d, das quais: \n%d linhas mal formatadas, %d linhas validadas\n", filename, nLinhas, linhasMal, nLinhas - linhasMal);
    fclose(file);
}

/**
 * Método Standard de leitura de inputs Numéricos
 * @return Input numérico(Inteiro)
 */
int nextInt(int min, int max) {
    int opcao = -1;

    scanf("%d", &opcao);
    getchar();
    while ((opcao < min) || (opcao > max)) {
        printf("Opção inválida\nIntroduza um valor entre %d e %d\n", min, max);
        scanf("%d", &opcao);
        getchar();
    }
    return opcao;
}

/**
 * Método Standard de leitura de inputs textuais
 * @return Input textual(String)
 */
char* nextString() {
    char* inp = malloc(100 * sizeof (char));
    fgets(inp, 10, stdin);
    return strdup(inp);
}

void imprimecabecalho() {
    printf("GESTHIPER\n");
    printf("Laboratórios de informática III\n");
    printf("=============================================================\n");
}

void lenomeficheiro_IU(char* nomeficheiro, char *nomedefeito) {
    system("clear");
    imprimecabecalho();
    printf("Introduza o nome do ficheiro (Enter=%s)\n", nomedefeito);
    scanf("%[^\n]", nomeficheiro);
    getchar();
    if (strcmp(nomeficheiro, "") == 0) {
        strcpy(nomeficheiro, nomedefeito);
    }
}
/**
 * Menu de leitura de ficheiros
 * @param db Base de dados a ser carregada com os dados do ficheiro
 */
void leitura_IU(GHDB db) {
    int op, op1;
    char* nome;
    system("clear");
    op = printMenuLeitura();
    do {
        switch (op)
            case 1:
            {
                op1 = subMenuCli();
                do {
                    switch (op1)
                        case 1: 
                        leituraCli(db, "FichClientes.txt");
                        break;
                    case 2: 
                        nome = nextString();
                        leituraCli(db, nome);
                        break;
                } while (op1 != 0);
                break;
            }
        case 2:
        {
            op1 = subMenuProd();
            do {
                switch (op1)
                    case 1: 
                    leituraProd(db, "FichProdutos.txt");
                    break;
                case 2: 
                    nome = nextString();
                    leituraProd(db, nome);
                    break;
            } while (op1 != 0);
            break;
        }
        case 3:
        {
            op1 = subMenuComp();
            do {
                switch (op1)
                    case 1: leituraComp(db, "FichCompras.txt");
                    break;
                case 2: 
                    nome = nextString();
                    leituraComp(db, nome);
                    break;
            } while (op1 != 0);
            break;
        }
    } while (op != 0);
}
/**
 * Menu principal de leitura 
 * @return Opção escolhida
 */
int printMenuLeitura() {
    system("clear");
    printf("Carregamento de ficheiros\n");
    printf("1-Leitura de ficheiro de Clientes\n");
    printf("2-Leitura de ficheiro de Produtos\n");
    printf("3-Leitura de ficheiro de Compras\n");

    return nextInt(1, 3);
}
/**
 * Sub menu de Leitura de Clientes
 * @return Opção escolhida
 */
int subMenuCli() {
    system("clear");
    printf("1- FichClientes.txt\n");
    printf("2- Inserir Manualmente o nome\n");
    printf("\n0-Voltar ao menu anterior\n");
    return nextInt(0, 2);
}
/**
 * Sub menu de Leitura de Produtos
 * @return Opção escolhida
 */
int subMenuProd() {
    system("clear");
    printf("1- FichProdutos.txt\n");
    printf("2- Inserir Manualmente o nome\n");
    printf("\n0-Voltar ao menu anterior\n");
    return nextInt(0, 2);
}
/**
 * Sub menu de Leitura de Compras
 * @return Opção escolhida
 */
int subMenuComp() {
    system("clear");
    printf("1- FichCompras.txt\n");
    printf("2- Inserir Manualmente o nome\n");
    printf("\n0-Voltar ao menu anterior\n");
    return nextInt(0, 2);
}
/**
 * Menu Principal
 * @param db Base de dados a ser utilizada
 */
void menuPrincipal(GHDB db){
        system("clear");
	imprimecabecalho();
	printf("Menu Principal\n");
	printf("1-Consultas ao IndÃ­ce de Autores\n");
	printf("2-Consultas Ã s Estatisticas\n");
	printf("3-Consultas ao CatÃ¡logo de Autores\n");
	printf("\n0-Sair\n");
	
	return nextInt(0,3);
}
int main() {
    GHDB db = new();
    int inputN;
    char* inputT;
    imprimecabecalho();
    while (!allFilesLoaded(db)) {
        leitura_IU(db);
    }
    menuPrincipal(db);
    return 0;
}