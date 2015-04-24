#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "EstruturasAux.h"
#include "CusTypes.h"
#include "Catalog.h"
#include "Compras.h"
#include "Contabilidade.h"
#include "CusTypes.h"

typedef struct db {
    Catalog produtos, clientes;
    ComprasDB compras;
    CTree contabilidade;
} *GHDB;

GHDB newGHDB() {
    GHDB aux = malloc(sizeof (struct db));
    aux->clientes = newCat();
    aux->produtos = newCat();
    aux->contabilidade = newCT();
    aux->compras = newCDB();
    return aux;
}

GHDB GHDB_insertProd(GHDB db, Codigo codigo) {
    GHDB aux = db;
    aux->produtos = Cat_insert(aux->produtos, codigo);
    aux->compras = CDB_insertProduto(aux->compras, codigo);
    aux->contabilidade = CT_insert(aux->contabilidade, codigo);
    return aux;
}

GHDB GHDB_insertCli(GHDB db, Codigo codigo) {
    GHDB aux = db;
    aux->clientes = Cat_insert(aux->clientes, codigo);
    
    aux->compras = CDB_insertCliente(aux->compras, codigo);
    return aux;
}

GHDB GHDB_insertComp(GHDB db, Codigo codigoP, float valor, int qtd, char modo, Codigo codigoC, int mes) {
    GHDB aux = db;
    aux->compras = CDB_registerSale(aux->compras, codigoP, valor, qtd, modo, codigoC, mes);
    aux->contabilidade = CT_insereCompra(aux->contabilidade, codigoP, modo, qtd, valor, mes);
    return aux;
}

CodigoArray GHDB_getClientes(GHDB db, Codigo primeira_letra) {
    return Cat_getTreeToArray(db->clientes, primeira_letra);
}

CodigoArray GHDB_getProdutos(GHDB db, Codigo primeira_letra) {
    return Cat_getTreeToArray(db->produtos, primeira_letra);
}

VendasProduto GHDB_getContabilidadeProduto(GHDB db, Codigo produto, int mes) {
    return CT_getDadosProduto(db->contabilidade, produto, mes);
}

CodigoArray GHDB_getProdutosNuncaComprados(GHDB db) {
    return CT_produtosNaoComprados(db->contabilidade);
}

Table GHDB_getTabelaProdutos(GHDB db, Codigo codigo) {
    return CDB_getTabelaCompras(db->compras, codigo);
}

TabelaCSV GHDB_getRelacao(GHDB db) {
    TabelaCSV aux = newCSV();
    aux = CT_carregaCompras(db->contabilidade, aux);
    aux = CDB_carregaClientesCSV(db->compras, aux);
    return aux;
}

Par GHDB_procuraNaoUtilizados(GHDB db) {
    return CDB_procuraNaoUtilizados(db->compras);
}

Faturacao GHDB_criaLista(GHDB db, int lower, int higher) {
    return CT_criaLista(db->contabilidade, lower, higher);
}

CodigoArray GHDB_getCompraEmTodosOsMeses(GHDB db) {
    return CDB_compraTodos(db->compras);
}

CodigoArray GHDB_getTopCompras(GHDB db, Codigo codigo) {
    CodigoArray ca = CDB_getTopCompras(db->compras, codigo);
    return CA_getFirstN(ca, 3);
}

CodigoArray GHDB_getTopComprasMensal(GHDB db, Codigo codigo, int mes) {
    return CDB_getTopComprasMensal(db->compras, codigo, mes);
}

ListaDePCM GHDB_getClientesCompradores(GHDB db, Codigo codigo) {
    return CDB_clientesCompradores(db->compras, codigo);
}

CodigoArray GHDB_getNMaisVendidos(GHDB db, int n) {
    CodigoArray ca = AQ_getCodigosDecresc(CDB_produtosToQtdArvore(db->compras), newCA());
    return CA_getFirstN(ca, n);
}



Boolean GHDB_prodCodeNotExistent(GHDB db, Codigo codigoP) {
    return !(Cat_searchCode(db->produtos, codigoP));
}

Boolean GHDB_cliCodeNotExistent(GHDB db, Codigo codigoC) {
    return !(Cat_searchCode(db->clientes, codigoC));
}

GHDB GHDB_disposeReload(GHDB db) {
    return newGHDB();
}

void GHDB_disposeExit(GHDB db) {
    Cat_dispose(db->clientes);
    Cat_dispose(db->produtos);
    CDB_dispose(db->compras);
    CT_dispose(db->contabilidade);
    free(db);
}

void imprimecabecalho() {
    int i=system("clear");    
    printf("GESTHIPER\n");
    printf("Laboratórios de informática III\n");
    printf("=============================================================\n");
	(void)i;
}

int nextInt(int min, int max) {
    int opcao = -1;
	int i;
    i=scanf("%d", &opcao);
    getchar();
    while ((opcao < min) || (opcao > max)) {
        printf("Opção inválida\nIntroduza um valor entre %d e %d\n", min, max);
        i=scanf("%d", &opcao);
        getchar();
    }
    return opcao;
	(void)i;
}

char* nextString() {
char* res=malloc(20*sizeof(char*));
int i=scanf("%s",res);
return res;
(void)i;
}


int printMenu() {
    int i=system("clear");
    imprimecabecalho();
    printf("Menu Principal\n");
    printf("1-Consultas aos Catálogos\n");
    printf("2-Consultas Contabilísticas\n");
    printf("3-Consultas às Compras\n");
    printf("4-Recarregar Ficheiros\n");
    printf("\n0-Sair\n");

    return nextInt(0, 4);
	(void)i;
}

int printMenuLeitura() {
    int i=system("clear");
    imprimecabecalho();
    printf("Carregamento de ficheiros\n");
    printf("1-Leitura de ficheiro de Clientes\n");
    printf("2-Leitura de ficheiro de Produtos\n");
    printf("3-Leitura de ficheiro de Compras\n");

    return nextInt(1, 3);
	(void)i;
}

/**
 * 
 * @return opção escolhida
 */
int printSubMenuCatalogos() {
    int i=system("clear");
    imprimecabecalho();
    printf("1- Catálogo de Clientes - Listar Códigos Começados por Letra\n");
    printf("2- Catálogo de Produtos - Listar Códigos Começados por Letra\n");
    printf("\n0-Sair\n");
    return nextInt(0, 2);
	(void)i;
}

/**
 * 
 * @return opção escolhida
 */
int printSubMenuContabilidade() {
    int i=system("clear");
    imprimecabecalho();
    printf("1- (Querie 3)Dado um mês e um código de produto apresentar o número total de vendas em modo N e em modo P, e o total facturado\n");
    printf("2- (Querie 11)Para cada mês mostar o número de compras realizadas e o número total de clientes que realizaram tais compras\n");
    printf("3- (Querie 4) Lista de códigos de produtos que ninguém comprou;\n");
    printf("4- (Querie 7) Total de compras registadas e o total facturado num intervalo de meses\n");
    printf("\n0-Sair\n");
    return nextInt(0, 4);
	(void)i;
}

/**
 * 
 * @return opção escolhida
 */
int printSubMenuCompras() {
    int i=system("clear");
    imprimecabecalho();
    printf("1- (Querie 5) Tabela com o número total de produtos comprados por um cliente, mês a mês\n");
    printf("2- (Querie 8) Determinar os códigos dos clientes que compraram um dado produto, distinguido entre N e P \n");
    printf("3- (Querie 9) Determinar a lista de códigos de produtos que um cliente mais comprou num mês, por ordem descendente\n");
    printf("4- (Querie 10) Lista de códigos de clientes que realizaram compras em todos os meses do ano\n");
    printf("5- (Querie 12) Lista dos N produtos mais vendidos em todo o ano\n");
    printf("6- (Querie 13) Determinar quais os 3 produtos que um cliente mais comprou durante o ano\n");
    printf("7- (Querie 14) Número de clientes registados que não realizaram compras e número de produtos que ninguém comprou.\n");
    printf("\n0-Sair\n");
    return nextInt(0, 7);
	(void)i;
}

void navegacao(CodigoArray ca) {
    char choice;
    int size = CA_getSize(ca);
    int lower = 0;
    int upper = min(size, 20);
	printf("Irão ser apresentadas %d entradas, distribuidas por %d páginas\n",size,size/20);    
do {
        while (lower < upper) {
            printf("%d - %s\n", lower + 1, CA_get(ca, lower));
            lower++;
        }
        printf("Prima 'S' para descer, 'W' para subir e 'Q' para sair: ");
        choice = toupper(getchar());
        getchar();
	while (choice != 'S' && choice != 'W' && choice != 'Q') {
            printf("Prima em S para descer, W para subir ou Q para sair: ");
            choice = toupper(getchar());
            getchar();
        }
        switch (choice) {
            case 'S':
                upper += min(size - upper, 20);
                break;
            case 'W':
                lower -= 20;
                if (lower < 0) lower = 0;
                break;
            default:
                break;
        }
    } while (choice != 'Q' || upper != size);

}

void navegacaoLPCM(ListaDePCM lpcm) {
    char choice;
    int size = LPCM_getSize(lpcm);
    int lower = 0;
    int upper = min(size, 20);
    do {
        while (lower < upper) {
            printf("%d - %s,%c\n", lower + 1, PCM_getCodigo(LPCM_get(lpcm, lower)),PCM_getModo(LPCM_get(lpcm,lower)));
            lower++;
        }
        printf("Prima 'S' para descer, 'W' para subir e 'Q' para sair: ");
        choice = toupper(getchar());
        getchar();
        while (choice != 'S' && choice != 'W' && choice != 'Q') {
            printf("Prima em S para descer, W para subir ou Q para sair: ");
            choice = toupper(getchar());
            getchar();
        }
        switch (choice) {
            case 'S':
                upper += min(size - upper, 20);
                break;
            case 'W':
                lower -= 20;
                if (lower < 0) lower = 0;
                break;
            default:
                break;
        }
    } while (choice != 'Q' || upper != size);

}

/**
 * Sub menu de Leitura de Clientes
 * @return Opção escolhida
 */
int subMenuCli() {
    int i=system("clear");
    imprimecabecalho();
    printf("1- FichClientes.txt\n");
    printf("2- Inserir Manualmente o nome\n");
    printf("\n0-Voltar ao menu anterior\n");
    return nextInt(0, 2);
	(void)i;
}

/**
 * Sub menu de Leitura de Produtos
 * @return Opção escolhida
 */
int subMenuProd() {
    int i=system("clear");
    imprimecabecalho();
    printf("1- FichProdutos.txt\n");
    printf("2- Inserir Manualmente o nome\n");
    printf("\n0-Voltar ao menu anterior\n");
    return nextInt(0, 2);
	(void)i;
}

/**
 * Sub menu de Leitura de Compras
 * @return Opção escolhida
 */
int subMenuComp() {
    int i=system("clear");
    imprimecabecalho();
    printf("1- Compras.txt\n");
    printf("2- Inserir Manualmente o nome\n");
    printf("\n0-Voltar ao menu anterior\n");
    return nextInt(0, 2);
	(void)i;
}

GHDB leituraCli(GHDB db, char* filename) {
    GHDB aux=db;
    int nLinhas = 0;
    char linha[10];
    char *tok;
    FILE* file = fopen(filename, "r");
    if (file) {
        while (fgets(linha, 10, file) != NULL) {
            tok = strtok(linha, "\r\n");
            aux = GHDB_insertCli(aux, tok);
            nLinhas++;
        }
        printf("Nome do ficheiro: %s\n%d Linhas lidas\n", filename, nLinhas);
        fclose(file);
    } else printf("Não foi possível encontrar/abrir o ficheiro %s\n",filename);
    return aux;

}

/**
 * Método de Leitura de um ficheiro de Produtos e posterior carregamento na Base de Dados
 * @param db Base de Dados que será carregada com os dados do ficheiro
 * @param filename Nome do Ficheiro que contém os códigos de produto
 */
GHDB leituraProd(GHDB db, char* filename) {
    GHDB aux=db;
    int nLinhas = 0;
    char linha[10];
    char *tok;
    FILE* file = fopen(filename, "r");
    if (file) {
        while (fgets(linha, 10, file) != NULL) {
            tok = strtok(linha, "\r\n");
            aux = GHDB_insertProd(aux, tok);
            nLinhas++;
        }
        printf("Nome do ficheiro: %s\n%d Linhas lidas\n", filename, nLinhas);
        fclose(file);
    } else printf("Não foi possível encontrar/abrir o ficheiro %s\n",filename);
    return aux;
}

/**
 * Método de Leitura de um ficheiro de Compras, validação dos dados existentes e posterior carregamento na Base de Dados
 * @param db Base de Dados que será carregada com os dados do ficheiro
 * @param filename Nome do Ficheiro que contém as informações de compra
 */
GHDB leituraComp(GHDB db, char* filename) {
    GHDB aux=db;
    FILE* file = fopen(filename, "r");
    int nLinhas = 0, linhasMal = 0;
    char* linha=malloc(32*sizeof(char*));
    char *codigoP, *codigoC;
    float valor;
    int qtd, mes;
    char *modoaux, modo;

    int flag = 0;
    if (file) {
       while (fgets(linha, 32, file)) {
            flag = 0;
            codigoP = strtok(linha, " ");
	
            if (GHDB_prodCodeNotExistent(aux,codigoP)) {
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
            if (GHDB_cliCodeNotExistent(aux, codigoC) && flag == 0) {
                linhasMal++;
                flag = 1;
            }
            mes = atoi(strtok(NULL, "\r\n"));
            if ((mes < 1 || mes > 12) && flag == 0) {
                linhasMal++;
                flag = 1;
            }
            nLinhas++;
		            
if (!flag) aux = GHDB_insertComp(aux, codigoP, valor, qtd, modo, codigoC, mes);
        }
        printf("Nome do ficheiro: %s\nNumero de Linhas Lidas: %d, das quais: \n%d linhas mal formatadas, %d linhas validadas\n", filename, nLinhas, linhasMal, nLinhas - linhasMal);
        fclose(file);
    } else printf("Não foi possível encontrar/abrir o ficheiro %s\n",filename);
    return aux;
}



/**
 * Menu de leitura de ficheiros
 * @param db Base de dados a ser carregada com os dados do ficheiro
 */
GHDB leituraFicheiros(GHDB db){
GHDB aux=db;
time_t start, end;
char *inputT;
imprimecabecalho();
printf("Insira o nome do ficheiro de Clientes: ");
inputT=nextString();
start=time(NULL);
aux=leituraCli(aux,inputT);
end=time(NULL);
printf("Leitura e lançamento para módulos realizado em %f segundos\n",difftime(end,start));
printf("Insira o nome do ficheiro de Produtos: ");
inputT=nextString();
start=time(NULL);
aux=leituraProd(aux,inputT);
end=time(NULL);
printf("Leitura e lançamento para módulos realizado em %f segundos\n",difftime(end,start));
printf("Insira o nome do ficheiro de Compras: ");
inputT=nextString();
start=time(NULL);
aux=leituraComp(aux,inputT);
end=time(NULL);
printf("Leitura e lançamento para módulos realizado em %f segundos\n",difftime(end,start));
getchar();
return aux;
}

/**
 * Menu Principal
 * @param db Base de dados a ser utilizada
 */
void menuPrincipal(GHDB db) {
    time_t start, end;
    int op, op1, inputN, mes, inputN1, contador;
    CodigoArray ca = newCA();
    VendasProduto vp;
    TabelaCSV tcsv;
    Faturacao ft;
    Table t;
    ListaDePCM lpcm;
    Par p;
    char* inputT;
    char choice;
    do {
        op = printMenu();
        switch (op) {
            case 1:
                do {
                    op1 = printSubMenuCatalogos();
                    switch (op1) {
                        case 1:
                        {
                            printf("Insira letra: ");
			    inputT = nextString();
                            ca = GHDB_getClientes(db, inputT);
                            navegacao(ca);
                            printf("\nPrima (ENTER) para continuar\n");
                            getchar();
                            break;
                        }
                        case 2:
                        {
                            printf("Insira letra: ");
 	 	            inputT = nextString();
                            ca = GHDB_getProdutos(db, inputT);
                            navegacao(ca);
                            printf("\nPrima (ENTER) para continuar\n");
                            getchar();
                            break;
                        }
                        default: break;
                    }
                } while (op1 != 0);
                printf("A sair do do Catálogo...\n");
                break;
            case 2:
                do {
                    op1 = printSubMenuContabilidade();

                    switch (op1) {
                        case 1:
                        {
                            printf("Digite um mês\n");
                            mes = nextInt(1, 12);
                            printf("Digite um codigo de produto\n");
                            inputT = nextString();
                            vp = GHDB_getContabilidadeProduto(db, inputT, mes);
                            printf("Vendas em modo N: %d\nVendas em modo P: %d\nTotal Faturado: %f\n", VP_getVendasN(vp), VP_getVendasP(vp), VP_getFaturacaoT(vp));
			    printf("\nPrima (ENTER) para continuar\n");                            
			    getchar();
	  		    getchar();


                            break;
                        }
                        case 2:
                        {
                            tcsv = GHDB_getRelacao(db);
                            printf("Insira o nome do ficheiro: ");
                            inputT = nextString();
                            CSV_toCsvFile(tcsv, inputT);
                            printf("Ficheiro gerado com sucesso\nPrima (ENTER) para continuar\n");
printf("\nPrima (ENTER) para continuar\n");
                            getchar();
                            

                            break;
                        }
                        case 3:
                        {
                            ca = GHDB_getProdutosNuncaComprados(db);
                            navegacao(ca);
                            printf("\nPrima (ENTER) para continuar\n");
                            getchar();

                            break;
                        }
                        case 4:
                        {
                            printf("Insira o limite inferior: ");
                            inputN = nextInt(1, 12);
                            printf("Insira o limite superior: ");
                            inputN1 = nextInt(1, 12);
                            ft = GHDB_criaLista(db, inputN, inputN1);
                            printf("Foram realizadas %d compras, faturando %f €\n", Fat_getNCompras(ft), Fat_getFaturacao(ft));
                            printf("\nPrima (ENTER) para continuar\n");
                            getchar();

                            break;
                        }
                        default: break;
                    }
                } while (op1 != 0);
                printf("A sair do módulo Contabilístico...\n");
                break;
            case 3:
            {
                do {
                    op1 = printSubMenuCompras();
                    switch (op1) {
                        case 1:
                        {
                            printf("Insira código de cliente: ");
                            inputT = nextString();
                            t = GHDB_getTabelaProdutos(db, inputT);
                            printf("Cliente: %s \n", Tab_getCodigo(t));
                            for (contador = 1; contador <= 12; contador++)
                                printf("Mês %d --> %d\n", contador, Tab_getCompras(t, contador));
                            printf("Pretende guardar os resultados em ficheiro? ((S)im/(N)ão): ");
                            choice = toupper(getchar());
                            getchar();
                            while (choice != 'S' && choice != 'N') {
                                printf("Prima S se pretender guardar em ficheiro\nPrima N caso contrário\n");
                                choice = toupper(getchar());
                                getchar();
                            }
                            if (choice == 'S') {
                                printf("Insira o nome de ficheiro: ");
                                inputT = nextString();
                                Tab_toTxtFile(t, inputT);
                                printf("\nEscrita concluída\n");
                            }
                            printf("\nPrima (ENTER) para continuar\n ");
                            getchar();

                            break;
                        }
                        case 2:
                        {
                            printf("Insira código de produto: ");
                            inputT = nextString();
                            start = time(NULL);
                            lpcm = GHDB_getClientesCompradores(db, inputT);
                            end = time(NULL);
                            printf("A leitura foi realizada em %f segundos\n", difftime(end, start));
                            navegacaoLPCM(lpcm);
                            printf("\nPrima (ENTER) para continuar\n ");
                            getchar();

                            break;
                        }
                        case 3:
                        {
                            printf("Insira código de Cliente: ");
                            inputT = nextString();
                            printf("Insira mês (1-12): ");
                            inputN = nextInt(1, 12);
                            start = time(NULL);
                            ca = GHDB_getTopComprasMensal(db, inputT, inputN);
                            end = time(NULL);
                            printf("A leitura foi realizada em %f segundos\n", difftime(end, start));
                            navegacao(ca);
                            printf("\nPrima (ENTER) para continuar\n ");
                            getchar();

                            break;
                        }
                        case 4:
                        {
                            ca = GHDB_getCompraEmTodosOsMeses(db);
                            navegacao(ca);
                            printf("\nPrima (ENTER) para continuar\n ");
                            getchar();

                            break;
                        }
                        case 5:
                        {
                            printf("Insira o número de produtos: ");
                            inputN = nextInt(1, 10000);
                            start = time(NULL);
                            ca = GHDB_getNMaisVendidos(db, inputN);
                            end = time(NULL);
                            printf("A leitura foi realizada em %f segundos\n", difftime(end, start));
                            navegacao(ca);
                            printf("\nPrima (ENTER) para continuar\n ");
                            getchar();

                            break;
                        }
                        case 6:
                        {
                            printf("Insira o código de cliente: ");
                            inputT = nextString();
                            ca = GHDB_getTopCompras(db, inputT);
                            for (contador = 0; contador < 3; contador++)
                                printf("%d - %s\n", contador + 1, CA_get(ca, contador));
                            printf("\nPrima (ENTER) para continuar\n ");
                            getchar();

                            break;
                        }
                        case 7:
                        {
                            p = GHDB_procuraNaoUtilizados(db);
                            printf("Clientes que não realizaram compras: %d\n", Par_getClientesSemCompras(p));
                            printf("Produtos que nunca foram comprados: %d\n", Par_getProdutosNaoComprados(p));
                            printf("\nPrima (ENTER) para continuar\n ");
                            getchar();

                            break;
                        }
			
                        default: break;
                    }
                } while (op1 != 0);
                printf("A sair do módulo de Compras...\n");
                break;
            }
		case 4: {
		db=GHDB_disposeReload(db);
		db=leituraFicheiros(db);
		}
        }
    } while (op != 0);

}

int main() {
    GHDB db = newGHDB();
    imprimecabecalho();
    db=leituraFicheiros(db);
    menuPrincipal(db);
	printf("A sair do GESTHIPER...\n");
    return 0;
}

