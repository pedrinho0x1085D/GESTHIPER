#GESTHIPER

Projecto Prático da Unidade Curricular de Laboratórios de Informática III

Linguagem: C

O projecto a desenvolver em C (usando gcc), de nome GESTHIPER, tem como fonte de dados três ficheiros de texto disponibilizados no BB da disciplina. No ficheiro FichProdutos.txt cada linha representa o código de um produto vendável no hipermercado, sendo cada código formado por duas letras maiúsculas e 4 dígitos, cf. os exemplos,

SO6315

ZX3085

HO2918

O ficheiro de produtos conterá 200.000 códigos de produto. No ficheiro FichClientes.txt cada linha representa o código de um cliente identificado do hipermercado, sendo cada código de cliente formado por duas letras maiúsculas e
3 dígitos, cf. os exemplos:

BP803

DS377

FH922

O ficheiro de clientes conterá 20.000 códigos de cliente. O ficheiro que será a maior fonte de dados do projecto designa-se por Compras.txt, no qual cada linha representa o registo de uma compra efectuada no hipermercado. Cada
linha (ou registo de compra) será formada por um código de produto, um preço unitário decimal, o número inteiro de unidades compradas, a letra N ou P conforme tenha sido uma compra Normal ou uma compra em Promoção, o código do cliente e o mês (1 ..12) da compra, cf. os exemplos seguintes: 

WJ3256 4.72 2 N AF651 10

QS7713 6.6 3 P FY106 3

UO4148 0.96 2 P BS944 12

ZO3863 13.24 4 P EU953 8

NE4370 17.25 1 P CP641 8

BF9686 0.31 3 N BU471 11

ZT8680 20.77 5 P AL332 5

##Melhorias a realizar:

-->Refazer a lista de Códigos de forma a ser alocada estaticamente.

-->Refazer a medição de tempo de forma a conseguir maior precisão.

Classificação: 13/20
