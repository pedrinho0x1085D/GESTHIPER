CC:=gcc
CFLAGS:=-ansi -O2 -Wall -pedantic 
TARGET:=GESTHIPER

all: $(TARGET)

$(TARGET): Main.o Catalog.o  Contabilidade.o Compras.o EstruturasAux.o CusTypes.o
	$(CC) $(CFLAGS) $^ -o $@ 

Main.o: Main.c 
	$(CC) $(CFLAGS) -c $^ 


Contabilidade.o: Contabilidade.c 
	$(CC) $(CFLAGS) -c $^ 

Catalog.o: Catalog.c  
	$(CC) $(CFLAGS) -c $^ 
	

Compras.o: Compras.c 
	$(CC) $(CFLAGS) -c $^ 

EstruturasAux.o: EstruturasAux.c 
	$(CC) $(CFLAGS) -c $^ 

CusTypes.o: CusTypes.c
	$(CC) $(CFLAGS) -c $^ 

	
clean: 
	@$(RM) *.o
	@echo Limpo