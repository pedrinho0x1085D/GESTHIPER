/*
 *        __      __   ______
 *       / /     / /  |____  \
 *      / /     / /     ___| |
 *     / /     / /     |___  |
 *    / /___  / /      ____| |
 *   /_____/ /_/      |______/
 *
 *
 *  Ficheiro: EstruturasAux.h
 *
 */

#ifndef ESTRUTURASAUX_H
#define	ESTRUTURASAUX_H

typedef char* Codigo;
typedef Codigo* CodigoArray;
/**
 * Inicialização de um array de códigos
 * @return Array de Códigos 
 */
CodigoArray newCA();

int CA_getSize(CodigoArray ca);
/**
 * Inserção de um Código num Array
 * @param ca Array de Códigos que vai receber o código
 * @param co Código a ser inserido
 */
CodigoArray CA_insert(CodigoArray ca, Codigo co);
/**
 * Libertação de espaço(Remoção do objecto)
 * @param ca Objecto a ser apagado
 */
void CA_dispose(CodigoArray ca);
/**
 * Verifica se um Código encontra-se num Array de códigos
 * @param co Código a ser procurado
 * @param ca Array de códigos a ser consultado
 * @return 1 caso o código exista, 0 caso contrário
 */
int CA_in(Codigo co, CodigoArray ca);

/**
 * 
 * @param ca Array de códigos
 * @param i Posição
 * @return Código indexado na posição i.
 */
Codigo CA_get(CodigoArray ca, int i);

CodigoArray CA_getFirstN(CodigoArray ca, int n);

typedef struct auxR2* VendasProduto;
VendasProduto newVP(int vendasN, int vendasP, float fatura);
int VP_getVendasN(VendasProduto aux);
int VP_getVendasP(VendasProduto aux);
float VP_getFaturacaoT(VendasProduto aux);
void VP_dispose(VendasProduto r2);

typedef struct auxilQ7* Faturacao;
Faturacao newFat();
void Fat_dispose(Faturacao aux);
float Fat_getFaturacao(Faturacao aux);
int Fat_getNCompras(Faturacao aux);
Faturacao Fat_insereCompra(Faturacao auxil, float valor, int qtd);

typedef struct tabela* Table;
Table newTab(Codigo codigo);
Table Tab_addValor(Table t, int qtd, int mes);
Codigo Tab_getCodigo(Table t);
int Tab_getCompras(Table t, int mes);
void Tab_dispose(Table t);
void Tab_toTxtFile(Table t, char* filename);

typedef struct tableQ11* TabelaCSV;
TabelaCSV newCSV();
TabelaCSV CSV_addCliente(TabelaCSV tcsv, int mes);
TabelaCSV CSV_addCompra(TabelaCSV tcsv, int mes);
void CSV_dispose(TabelaCSV tcsv);
void CSV_toCsvFile(TabelaCSV csv, char* filename);
TabelaCSV CSV_addCompras(TabelaCSV tcsv, int mes, int vezes);

typedef struct par* Par;
Par newPar();
void Par_dispose(Par p);
Par Par_addCliente(Par p);
Par Par_addProduto(Par p);
int Par_getClientesSemCompras(Par p);
int Par_getProdutosNaoComprados(Par p);


typedef struct nodeTop* TreeTop;
TreeTop TT_newNode(Codigo codigo, int totalQtd);
TreeTop TT_insertNode(TreeTop arvore, Codigo codigo, int totalQtd);
CodigoArray TT_maisComprados(TreeTop tt, CodigoArray ca);
void TT_dispose(TreeTop tt);
CodigoArray TT_topCompras(TreeTop aux);


typedef struct arvoreQ8* ArvoreClientes;
ArvoreClientes newAC();
ArvoreClientes AC_newNode(Codigo codigo, char modo);
ArvoreClientes AC_insert(ArvoreClientes ac, Codigo codigo, char modo);
int AC_contaClientesDif(ArvoreClientes ac);
void AC_dispose(ArvoreClientes ac);
int AC_contaDiffCli(ArvoreClientes ac, CodigoArray ca);


typedef struct treeQ12* ArvoreQtd;
ArvoreQtd newAQ();
ArvoreQtd AQ_newNode(Codigo codigo, int qtd);
void AQ_dispose(ArvoreQtd aq);
ArvoreQtd AQ_insert(ArvoreQtd aq, Codigo codigo, int qtd);
CodigoArray AQ_getCodigosDecresc(ArvoreQtd aq, CodigoArray ca);


typedef struct parCodModo* ParCodigoModo;
ParCodigoModo newPCM(Codigo codigo, char modo);
Codigo PCM_getCodigo(ParCodigoModo pcm);
char PCM_getModo(ParCodigoModo pcm);
void PCM_dispose(ParCodigoModo pcm);


typedef ParCodigoModo* ListaDePCM;
ListaDePCM newLPCM();
int LPCM_getSize(ListaDePCM lpcm);
ListaDePCM LPCM_insert(ListaDePCM lpcm, Codigo codigo, char modo);
ParCodigoModo LPCM_get(ListaDePCM lpcm, int pos);
void LPCM_dispose(ListaDePCM lpcm);
ListaDePCM LPCM_getFirstN(ListaDePCM lpcm, int n);

typedef struct parCodQtd* ParCodigoQtd;
ParCodigoQtd newPCQ(Codigo codigo, int qtd);
Codigo PCQ_getCodigo(ParCodigoQtd pcq);
int PCQ_getQtd(ParCodigoQtd pcq);
void PCQ_dispose(ParCodigoQtd pcq);


typedef ParCodigoQtd* ListaDePCQ;
ListaDePCQ newLPCQ();
int LPCQ_getSize(ListaDePCQ lpcq);
ListaDePCQ LPCQ_insert(ListaDePCQ lpcq, Codigo codigo, int qtd);
ParCodigoQtd LPCQ_get(ListaDePCQ lpcq, int pos);
void LPCQ_dispose(ListaDePCQ lpcq);
ListaDePCQ LPCQ_getFirstN(ListaDePCQ lpcq, int n);
CodigoArray TT_travessiaDecrescente(TreeTop tt, CodigoArray ca);
TreeTop TT_update(TreeTop tt, Codigo codigo, int qtdTotal);
ListaDePCM AC_travessiaArvore(ArvoreClientes ac, ListaDePCM l);
ListaDePCQ AQ_travessiaDecrescente(ArvoreQtd aq, ListaDePCQ l);
#endif	/* CODIGO_H */

