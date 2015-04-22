CC:=gcc
CFLAGS:=-ansi -O2 -Wall -pedantic 
TARGET:=GESTHIPER

all: $(TARGET)

$(TARGET): Main.o Catalog.o AVLTree.o GHDB.o Contabilidade.o Compras.o EstruturasAux.o CusTypes.o
	$(CC) $(CFLAGS) $^ -o $@ 

Main.o: Main.c GHDB.o EstruturasAux.o
	$(CC) $(CFLAGS) -c $^

GHDB.o: GHDB.c GHDB.h Catalog.o Compras.o Contabilidade.o CusTypes.o
	$(CC) $(CFLAGS) -c $^

Contabilidade.o: Contabilidade.c Contabilidade.h EstruturasAux.o CusTypes.o
	$(CC) $(CFLAGS) -c $^

Catalog.o: Catalog.c Catalog.h EstruturasAux.o AVLTree.o CusTypes.o
	$(CC) $(CFLAGS) -c $^
	
AVLTree.o: AVLTree.c AVLTree.h EstruturasAux.o Compras.c Compras.h
	$(CC) $(CFLAGS) -c $^

Compras.o: Compras.c Compras.h EstruturasAux.o AVLTree.c AVLTree.h CusTypes.o
	$(CC) $(CFLAGS) -c $^

EstruturasAux.o: EstruturasAux.c EstruturasAux.h 
	$(CC) $(CFLAGS) -c $^

CusTypes.o: CusTypes.h CusTypes.c
	$(CC) $(CFLAGS) -c $^

	
clean: 
	@$(RM) *.o
	@echo Limpo
