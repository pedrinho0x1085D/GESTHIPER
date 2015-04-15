/* 
 * File:   Codigo.h
 * Author: iFilipe
 *
 * Created on 11 de Março de 2015, 15:23
 */

#ifndef ESTRUTURASAUX_H
#define	ESTRUTURASAUX_H

typedef char* Codigo;
typedef Codigo* CodigoArray;
/**
 * Inicialização de um array de códigos
 * @return Array de Códigos 
 */
CodigoArray new();

int getSize(CodigoArray ca);
/**
 * Inserção de um Código num Array
 * @param ca Array de Códigos que vai receber o código
 * @param co Código a ser inserido
 */
CodigoArray insert(CodigoArray ca, Codigo co);
/**
 * Libertação de espaço(Remoção do objecto)
 * @param ca Objecto a ser apagado
 */
void dispose(CodigoArray ca);
/**
 * Verifica se um Código encontra-se num Array de códigos
 * @param co Código a ser procurado
 * @param ca Array de códigos a ser consultado
 * @return 1 caso o código exista, 0 caso contrário
 */
int in(Codigo co, CodigoArray ca);
/**
 * Retorna o mínimo entre dois inteiros
 * @return O mínimo entre dois inteiros
 */
int min(int x1,int x2);
/**
 * 
 * @param ca Array de códigos
 * @param i Posição
 * @return Código indexado na posição i.
 */
Codigo get(CodigoArray ca, int i);

CodigoArray getFirstN(CodigoArray ca, int n);

typedef struct auxR2* AuxR2;
AuxR2 new(int vendasN,int vendasP,float fatura);
int getVendasN(AuxR2 aux);
int getVendasP(AuxR2 aux);
float getFaturacaoT(AuxR2 aux);
AuxR2 getDadosProduto(CTree ct, Codigo codigo, int mes);

typedef struct auxilQ7* AuxQ7;
AuxQ7 new();
void dispose(AuxQ7 aux);
float getFaturacao(AuxQ7 aux);
int getNCompras(AuxQ7 aux);
AuxQ7 insereCompra(AuxQ7 auxil, float valor,int qtd);

typedef struct tabela* Table;
Table new(Codigo codigo);
Table addValor(Table t, int qtd, int mes);
Codigo getCodigo(Table t);
int getCompras(Table t, int mes);
void dispose(Table t);
void toTxtFile(Table t,char* filename);

typedef struct tableQ11* TabelaCSV;
TabelaCSV new();
TabelaCSV addCliente(TabelaCSV tcsv, int mes);
TabelaCSV addCompra(TabelaCSV tcsv, int mes);
void dispose(TabelaCSV tcsv);
void toCsvFile(TabelaCSV csv,char* filename);

typedef struct par* Par;
Par new();
Par dispose(Par p);
Par addCliente(Par p);
Par addProduto(Par p);
int getClientesSemCompras(Par p);
int getProdutosNaoComprados(Par p);

int in(int x,int linf,int lsup);

typedef struct nodeTop* TreeTop;
TreeTop newNode(Codigo codigo,int totalQtd);
TreeTop insertNode(TreeTop arvore, Codigo codigo,int totalQtd);

CodigoArray topCompras(TreeTop aux);

typedef struct arvoreQ8* ArvoreClientes;
ArvoreClientes new();
ArvoreClientes newNode();
ArvoreClientes insert(ArvoreClientes ac, Codigo codigo, char modo);
int contaClientesDif(ArvoreClientes ac);
ArvoreClientes produtoToArvoreCl(Produto p);
void dispose(ArvoreClientes ac);


typedef struct treeQ12* ArvoreQtd;
ArvoreQtd new();
ArvoreQtd new(Codigo codigo, int qtd);
void dispose(ArvoreQtd aq);
ArvoreQtd insert(ArvoreQtd aq, Codigo codigo, int qtd);
CodigoArray getCodigosDecresc(ArvoreQtd aq);

typedef struct parCodModo* ParCodigoModo;
ParCodigoModo new(Codigo codigo, char modo);
Codigo getCodigo(ParCodigoModo pcm);
char getModo(ParCodigoModo pcm);
void dispose(ParCodigoModo pcm);


typedef ParCodigoModo* ListaDePCM;
ListaDePCM new();
int getSize(ListaDePCM lpcm);
ListaDePCM insert(ListaDePCM lpcm,Codigo codigo,char modo);
ParCodigoModo get(ListaDePCM lpcm,int pos);
void dispose(ListaDePCM lpcm);
ListaDePCM getFirstN(ListaDePCM lpcm, int n);

typedef struct parCodQtd* ParCodigoQtd;
ParCodigoQtd new(Codigo codigo, int qtd);
Codigo getCodigo(ParCodigoQtd pcq);
int getQtd(ParCodigoQtd pcq);
void dispose(ParCodigoQtd pcq);

typedef struct parCodQtd* ListaDePCQ;
ListaDePCQ new();
int getSize(ListaDePCQ lpcq);
ListaDePCQ insert(ListaDePCQ lpcq,Codigo codigo,char modo);
ParCodigoQtd get(ListaDePCQ lpcq,int pos);
void dispose(ListaDePCQ lpcq);
ListaDePCQ getFirstN(ListaDePCQ lpcq, int n);
#endif	/* CODIGO_H */

