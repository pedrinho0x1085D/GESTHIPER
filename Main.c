#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "GHDB.h"
#include "EstruturasAux.h"

/**
 * Método de Leitura de um ficheiro de clientes e posterior carregamento na Base de Dados
 * @param db Base de Dados que será carregada com os dados do ficheiro
 * @param filename Nome do Ficheiro que contém os códigos de cliente
 */
GHDB leituraCli(GHDB db, char* filename) {
    if (GHDB_cliFileIsLoaded(db)) db=GHDB_disposeReload(db);
    int nLinhas = 0;
    char linha[10];
    char *tok;
    FILE* file = fopen(filename, "r");
    while (fgets(linha, 10, file) != NULL) {
        tok = strtok(linha, "\r\n");
        db = GHDB_insertCli(db, tok);
        nLinhas++;
    }
    db = GHDB_loadCliFile(db);
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
    if (GHDB_prodFileIsLoaded(db)) db=GHDB_disposeReload(db);
    int nLinhas = 0;
    char linha[10];
    char *tok;
    FILE* file = fopen(filename, "r");
    while (fgets(linha, 10, file) != NULL) {
        tok = strtok(linha, "\r\n");
        db = GHDB_insertProd(db, tok);
        nLinhas++;
    }
    db = GHDB_loadProdFile(db);
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

    if (GHDB_comFileIsLoaded(db))
        db=GHDB_disposeReload(db);

    while (fgets(linha, 30, file) != NULL) {
        flag = 0;
        codigoP = strtok(linha, " ");
        if (GHDB_prodCodeNotExistent(db, codigoP)) {
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
        if (GHDB_cliCodeNotExistent(db, codigoP) && flag == 0) {
            linhasMal++;
            flag = 1;
        }
        mes = atoi(strtok(NULL, " "));
        if (mes < 1 || mes > 12 && flag == 0) {
            linhasMal++;
            flag = 1;
        }
        nLinhas++;
        if (!flag) db = GHDB_insertComp(db, codigoP, valor, qtd, modo, codigoC, mes);
    }
    if (linhasMal != nLinhas) db = GHDB_loadComFile(db);
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
    time_t start,end;
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
                            start=time(NULL);
                        db = leituraCli(db, "FichClientes.txt");
                        end=time(NULL);
                        printf("A leitura foi realizada em %f segundos\n",difftime(end,start));
                    break;
                    case 2:
                    nome = nextString();
                    start=time(NULL);
                    db = leituraCli(db, nome);
                    end=time(NULL);
                    printf("A leitura foi realizada em %f segundos\n",difftime(end,start));
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
                    start=time(NULL);
                    db = leituraProd(db, "FichProdutos.txt");
                    end=time(NULL);
                    printf("A leitura foi realizada em %f segundos\n",difftime(end,start));
                break;
                case 2:
                nome = nextString();
                start=time(NULL);
                db = leituraProd(db, nome);
                end=time(NULL);
                printf("A leitura foi realizada em %f segundos\n",difftime(end,start));
                break;
            } while (op1 != 0);
            break;
        }
        case 3:
        {
            op1 = subMenuComp();
            do {
                switch (op1)
                    case 1: 
                        start=time(NULL);
                        db = leituraComp(db, "FichCompras.txt");
                    end=time(NULL);
                    printf("A leitura foi realizada em %f segundos\n",difftime(end,start));
                break;
                case 2:
                nome = nextString();
                start=time(NULL);
                db = leituraComp(db, nome);
                end=time(NULL);
                    printf("A leitura foi realizada em %f segundos\n",difftime(end,start));
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
    time_t start,end;
    int op, op1, inputN, mes,inputN1,contador;
    CodigoArray ca =new();
    VendasProduto vp;
    TabelaCSV tcsv;
    Faturacao ft;
    Table t;
    ListaDePCM lpcm;
    Par p;
    char* inputT;
    do {
    op = printMenu();
        switch (op)
            case 1:
            do {
                op1 = printSubMenuCatalogos();
                switch (op1)
                    case 1:
                    inputT = nextString();
                ca = GHDB_getClientes(db, inputT);
                printf("Irão ser apresentadas %d entradas\n", CA_getSize(ca));
                navegacao(ca);
                printf("\nPrima (ENTER) para continuar\n");
                getchar();
                dispose(ca);
                break;
                case 2:
                inputT = nextString();
                ca = GHDB_getProdutos(db, inputT);
                printf("Irão ser apresentadas %d entradas\n", CA_getSize(ca));
                navegacao(ca);
                printf("\nPrima (ENTER) para continuar\n");
                getchar();
                dispose(ca);
                break;
            } while (op1 != 0);
            printf("A sair do do Catálogo...\n");
        break;
        case 2:
        do {
            op1 = printSubMenuContabilidade();

            switch (op1)
                case 1:
                printf("Digite um mês\n");
                mes = nextInt(1, 12);
                printf("Digite um codigo de produto\n");
                inputT = nextString();
                vp = GHDB_getContabilidadeProduto(db, inputT, mes);
                printf("Vendas em modo N: %d\nVendas em modo P: %d\nTotal Faturado: %f\n", VP_getVendasN(vp), VP_getVendasP(vp), VP_getFaturacaoT(vp));
                getchar();
                dispose(vp);
            break;
            case 2:
                tcsv = GHDB_getRelacao(db);
                printf("Insira o nome do ficheiro: ");
                inputT = nextString();
                CSV_toCsvFile(tcsv, inputT);
                printf("Ficheiro gerado com sucesso\nPrima (ENTER) para continuar\n");
                getchar();
                dispose(tcsv);
            break;
            case 3:
                ca=GHDB_getProdutosNuncaComprados(db);
                navegacao(ca);
                printf("\nPrima (ENTER) para continuar\n");
                getchar();
                dispose(ca);
            break;
            case 4:
                printf("Insira o limite inferior: ");
                inputN=nextInt(1,12);
                printf("Insira o limite superior: ");
                inputN1=nextInt(1,12);
                ft=GHDB_criaLista(db,inputN, inputN1);
                printf("Foram realizadas %d compras, faturando %f €\n",Fat_getNCompras(ft),Fat_getFaturacao(ft));
                printf("\nPrima (ENTER) para continuar\n");
                getchar();
                dispose(ft);
            break;
        } while (op1 != 0);
        printf("A sair do módulo Contabilístico...\n");    
        break;
        case 3:
        do {
            op1 = printSubMenuCompras();
            switch (op1)
                case 1:
                    printf("Insira código de cliente: ");
                    inputT=nextString();
                    t=GHDB_getTabelaProdutos(db,inputT);
                    printf("Cliente: %s \n",getCodigo(t));
                    for(contador=1;contador<=12;contador++)
                        printf("Mês %d --> ",contador,getCompras(t,contador));
                    printf("\nPrima (ENTER) para continuar\n ");
                    getchar();
                    dispose(t);
                break;
                case 2:
                    printf("Insira código de produto: ");
                    inputT=nextString();
                    start=time(NULL);
                    lpcm=GHDB_getClientesCompradores(db,inputT);
                    end=time(NULL);
                    printf("A leitura foi realizada em %f segundos\n",difftime(end,start));
                    navegacao(lpcm);
                    printf("\nPrima (ENTER) para continuar\n ");
                    getchar();
                    dispose(lpcm);
                break;
                case 3:
                    printf("Insira código de Cliente: ");
                    inputT=nextString();
                    printf("Insira mês (1-12): ");
                    inputN=nextInt(1,12);
                    start=time(NULL);
                    ca=GHDB_getTopComprasMensal(db,inputT,inputN);
                    end=time(NULL);
                    printf("A leitura foi realizada em %f segundos\n",difftime(end,start));
                    navegacao(ca);
                    printf("\nPrima (ENTER) para continuar\n ");
                    getchar();
                    dispose(ca);
                break;
                case 4:
                    ca=GHDB_getCompraEmTodosOsMeses(db);
                    navegacao(ca);
                    printf("\nPrima (ENTER) para continuar\n ");
                    getchar();
                    dispose(ca);
                break;
                case 5:
                    printf("Insira o número de produtos: ");
                    inputN=nextInt(1,10000);
                    start=time(NULL);
                    ca=GHDB_getNMaisVendidos(db,inputN);
                    end=time(NULL);
                    printf("A leitura foi realizada em %f segundos\n",difftime(end,start));
                    navegacao(ca);
                    printf("\nPrima (ENTER) para continuar\n ");
                    getchar();
                    dispose(ca);
                break;
                case 6:
                    printf("Insira o código de produto: ");
                    inputT=nextString();
                    ca=GHDB_getNMaisVendidos(db,inputT);
                    for(contador=0;contador<3;contador++)
                        printf("%d - %s\n",contador+1,get(ca,contador));
                    printf("\nPrima (ENTER) para continuar\n ");
                    getchar();
                    dispose(ca);
                break;
                case 7:
                    p=GHDB_procuraNaoUtilizados(db);
                    printf("Clientes que não realizaram compras: %d\n",Par_getProdutosNaoComprados(p));
                    printf("Produtos que nunca foram comprados: %d\n",Par_getClientesSemCompras(p));
                    printf("\nPrima (ENTER) para continuar\n ");
                    getchar();
                    dispose(p);
                break;
     

   
        } while (op1 != 0);
        break;
        printf("A sair do módulo de Compras...\n");
    } while (op != 0);

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
int printSubMenuContabilidade() {
    system("clear");
    imprimecabecalho();
    printf("1- (Querie 3)Dado um mês e um código de produto apresentar o número total de vendas em modo N e em modo P, e o total facturado\n");
    printf("2- (Querie 11)Para cada mês mostar o número de compras realizadas e o número total de clientes que realizaram tais compras\n");
    printf("3- (Querie 4) Lista de códigos de produtos que ninguém comprou;\n");
    printf("4- (Querie 7) Total de compras registadas e o total facturado num intervalo de meses\n");
    printf("\n0-Sair\n");
    return nextInt(0, 4);
}

/**
 * 
 * @return opção escolhida
 */
int printSubMenuCompras() {
    system("clear");
    imprimecabecalho();
    printf("1- (Querie 5) Tabela com o número total de produtos comprados por um cliente, mês a mês\n");
    printf("2- (Querie 8) Determinar os códigos dos clientes que compraram um dado produto, distinguido entre N e P \n");
    printf("3- (Querie 9) Determinar a lista de códigos de produtos que um cliente mais comprou num mês, por ordem descendente\n");
    printf("4- (Querie 10) Lista de códigos de clientes que realizaram compras em todos os meses do ano\n");
    printf("5- (Querie 12) Lista dos N produtos mais vendidos em todo o ano\n");
    printf("6- (Querie 13) Determinar quais os 3 produtos que um cliente mais comprou durante o ano\n;")
    printf("7- (Querie 14) Número de clientes registados que não realizaram compras e número de produtos que ninguém comprou.\n")
    printf("\n0-Sair\n");
    return nextInt(0, 7);
}

void navegacao(CodigoArray ca) {
    char choice;
    int size=CA_getSize(ca);
    int lower=0;
    int upper=min(size,20);
        do{
        while(lower<upper){
            printf("%d - %s\n",lower+1,get(ca,lower));
            lower++;
        }
        printf("Prima 'S' para descer, 'W' para subir e 'Q' para sair: ");
        choice=toupper(getchar());
        getchar();
        while(choice!='S'&&choice!='W'&&choice!='Q'){
            printf("Prima em S para descer, W para subir ou Q para sair");
            choice=toupper(getchar());
            getchar();
        }
        switch(choice)
                case 'S':
                    upper+=min(size-upper,20);
                    break;
                case 'W':
                    lower-=20;
                    if(lower<0) lower=0;
                    break;
                default:
                    break;
                        
    }
    while(choice!='q'||upper!=size);
    
}


void navegacao(ListaDePCM lpcm){
    char choice;
    int size=LPCM_getSize(lpcm);
    int lower=0;
    int upper=min(size,20);
    do{
        while(lower<upper){
            printf("%d - %s\n",lower+1,get(lpcm,lower));
            lower++;
        }
        printf("Prima 'S' para descer, 'W' para subir e 'Q' para sair: ");
        choice=toupper(getchar());
        getchar();
        while(choice!='S'&&choice!='W'&&choice!='Q'){
            printf("Prima em S para descer, W para subir ou Q para sair");
            choice=toupper(getchar());
            getchar();
        }
        switch(choice)
                case 'S':
                    upper+=min(size-upper,20);
                    break;
                case 'W':
                    lower-=20;
                    if(lower<0) lower=0;
                    break;
                default:
                    break;
                        
    }
    while(choice!='q'||upper!=size);
    
}

int min(int x1,int x2){
    if(x1<x2) return x1;
    else if(x1>x2) return x2;
    else return x1;
}

int max(int x1,int x2){
    if(x1>x2) return x1;
    else if(x2>x1) return x2;
    else return x1;
}
int main() {
    GHDB db = new();
    imprimecabecalho();
    while (!GHDB_allFilesLoaded(db)) {
        db = leitura_IU(db);
    }
    menuPrincipal(db);
    GHDB_disposeExit(db);
    return 0;
}

