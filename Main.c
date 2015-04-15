#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GHDB.h"
#include "EstruturasAux.h"

/**
 * Método de Leitura de um ficheiro de clientes e posterior carregamento na Base de Dados
 * @param db Base de Dados que será carregada com os dados do ficheiro
 * @param filename Nome do Ficheiro que contém os códigos de cliente
 */
GHDB leituraCli(GHDB db, char* filename) {
    if (cliFileIsLoaded(db)) disposeReload(db);
    int nLinhas = 0;
    char linha[10];
    char *tok;
    FILE* file = fopen(filename, "r");
    while (fgets(linha, 10, file) != NULL) {
        tok = strtok(linha, "\r\n");
        db=insertCli(db, tok);
        nLinhas++;
    }
    loadCliFile(db);
    printf("Nome do ficheiro: %s\n%d Linhas lidas\n", filename, nLinhas);
    fclose(file);
    return db;
}

/**
 * Método de Leitura de um ficheiro de Produtos e posterior carregamento na Base de Dados
 * @param db Base de Dados que será carregada com os dados do ficheiro
 * @param filename Nome do Ficheiro que contém os códigos de produto
 */
GHDB leituraProd(GHDB db, char* filename) {
    if (prodFileIsLoaded(db)) disposeReload(db);
    int nLinhas = 0;
    char linha[10];
    char *tok;
    FILE* file = fopen(filename, "r");
    while (fgets(linha, 10, file) != NULL) {
        tok = strtok(linha, "\r\n");
        db=insertProd(db, tok);
        nLinhas++;
    }
    loadProdFile(db);
    printf("Nome do ficheiro: %s\n%d Linhas lidas\n", filename, nLinhas);
    fclose(file);
    return db;
}

/**
 * Método de Leitura de um ficheiro de Compras, validação dos dados existentes e posterior carregamento na Base de Dados
 * @param db Base de Dados que será carregada com os dados do ficheiro
 * @param filename Nome do Ficheiro que contém as informações de compra
 */
GHDB leituraComp(GHDB db, char* filename) {
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
        if (!flag) db=insertComp(db, codigoP, valor, qtd, modo, codigoC, mes);
    }
    if (linhasMal != nLinhas) loadComFile(db);
    printf("Nome do ficheiro: %s\nNumero de Linhas Lidas: %d, das quais: \n%d linhas mal formatadas, %d linhas validadas\n", filename, nLinhas, linhasMal, nLinhas - linhasMal);
    fclose(file);
    return db;
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
GHDB leitura_IU(GHDB db) {
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
    return db;
}

/**
 * Menu principal de leitura 
 * @return Opção escolhida
 */
int printMenuLeitura() {
    system("clear");
    imprimecabecalho();   
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
    imprimecabecalho();
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
    imprimecabecalho();
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
    imprimecabecalho();
    printf("1- FichCompras.txt\n");
    printf("2- Inserir Manualmente o nome\n");
    printf("\n0-Voltar ao menu anterior\n");
    return nextInt(0, 2);
}

/**
 * Menu Principal
 * @param db Base de dados a ser utilizada
 */
void menuPrincipal(GHDB db) {
    int op, op1, ano, inputN, mes;
    CodigoArray ca=new();
    char* inputT;
    op = printMenu();
    do {
        switch (op)
        case 1:
           do {
                op1=printSubMenuCatalogos();
                switch(op1)
                case 1: 
                inputT=nextString(); 
                ca=getClientes(db,inputT);
                printf("Irão ser apresentadas %d entradas\n",getSize(ca));
                /*Percorrer o ARRAY de 20 em 20 */
                break;
                case 2: 
                inputT=nextString(); 
                ca=getProdutos(db,inputT);
                printf("Irão ser apresentadas %d entradas\n",getSize(ca));
                /*Percorrer o ARRAY de 20 em 20 */
                break;           
                } 
           while (op1 != 0);
        break;
        case 2:
            do {
                op1=printSubMenuContabilidade();
                
                switch(op1)
                case 1: 
                printf("Digite um mês\n");
                scanf("%d", mes);
                getchar();
                printf("Digite um codigo de produto\n");
                inputT=nextString(); 
                getchar();
                //FUNÇÂO DA QUERIE 3
                break;
                case 2: 
                //Função que cria o ficheiro CSV
                break;           
                } 
           while (op1 != 0);
        break;
        case 3:
            do {
                op1=printSubMenuCompras();
                switch(op1)
                case 1: 
                
                break;
                case 2: 
                
                break;
                case 3: 
                
                break; 
                case 4: 
                
                break; 
                case 5: 
                
                break; 
                case 6: 
                
                break;
                case 7: 
                
                break;
                case 8: 
                
                break;
                case 9: 
                
                break; 
                } 
           while (op1 != 0);
        break;
            
    }    while (op != 0);
}
/**
 * 
 * @return opção escolhida
 */
int printMenu() {
    system("clear");
    imprimecabecalho();
    printf("Menu Principal\n");
    printf("1-Consultas aos Catálogos\n");
    printf("2-Consultas Contabilísticas\n");
    printf("3-Consultas às Compras\n");
    printf("\n0-Sair\n");

    return nextInt(0, 3);
}
/**
 * 
 * @return opção escolhida
 */
int printSubMenuCatalogos() {
    system("clear");
    imprimecabecalho();
    printf("1- Catálogo de Clientes - Listar Códigos Começados por Letra\n");
    printf("2- Catálogo de Produtos - Listar Códigos Começados por Letra\n");
    printf("\n0-Sair\n");
    return nextInt(0, 2);
}
/**
 * 
 * @return opção escolhida
 */
int printSubMenuContabilidade(){
    system("clear");
    imprimecabecalho();
    printf("1-(Querie 3)Dado um mês e um código de produto apresentar o número total de vendas em modo N e em modo P, e o total facturado\n"); 
    printf("2-(Querie 11)Para cada mês mostar o número de compras realizadas e o número total de clientes que realizaram tais compras\n");
    printf("\n0-Sair\n");
    return nextInt(0,2);
}
/**
 * 
 * @return opção escolhida
 */
int printSubMenuCompras(){
    system("clear");
    imprimecabecalho();
    printf("1- (Querie 4) Lista de códigos de produtos que ninguém comprou;\n");
    printf("2- (Querie 5) Tabela com o número total de produtos comprados, mês a mês\n");
    printf("3- (Querie 7) Total de compras registadas e o total facturado num intervalo de meses\n");
    printf("4- (Querie 8) Dado um produto, determinar os códigos dos clientes que o compraram, distinguido entre N e P \n");
    printf("5- (Querie 9) Determinar a lista de códigos de produtos que um cliente mais comprou, por ordem descendente\n");
    printf("6- (Querie 10) Lista de códigos de clientes que realizaram compras em todos os meses do ano\n");
    printf("7- (QUerie 12)Lista dos N produtos mais vendidos em todo o ano\n");
    printf("8- (Querie 13) Determinar quais os 3 produtos que um cliente mais comprou durante o ano\n;")
    printf("9- (Querie 14) Número de clientes registados que não realizaram compras e  número de produtos que ninguém comprou.\n")
    printf("\n0-Sair\n");
    return nextInt(0,9);
}


int main() {
    GHDB db = new();
    imprimecabecalho();
    while (!allFilesLoaded(db)) {
        db=leitura_IU(db);
    }
    menuPrincipal(db);
    return 0;
}