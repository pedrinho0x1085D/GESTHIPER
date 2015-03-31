CC:=gcc
CFLAGS:=-ansi -O2 -Wno-unused-result
TARGET:=GESTHIPER

all: $(TARGET)

$(TARGET): Main.o Catalog.o AVLTree.o 
	$(CC) $(CFLAGS) $^ -o $@ 

Main.o: Main.c 
	$(CC) $(CFLAGS) -c $^
#
#Catalogo_Produtos.o: Catalogo_Produtos.c Catalogo_Produtos.h arvoresAVL.o
#	$(CC) $(CFLAGS) -c $^

Catalog.o: Catalog.c Catalog.h AVLTree.o
	$(CC) $(CFLAGS) -c $^
	
AVLTree.o: AVLTree.c AVLTree.h
	$(CC) $(CFLAGS) -c $^

#leitura.o: leitura.c leitura.h
#	$(CC) $(CFLAGS) -c $^

#utils.o: utils.c utils.h
#	$(CC) $(CFLAGS) -c $^

clean: 
	@$(RM) *.o
	@echo Limpo
