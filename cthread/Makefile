#
# Makefile de EXEMPLO
#
# OBRIGATÓRIO ter uma regra "all" para geração da biblioteca e de uma
# regra "clean" para remover todos os objetos gerados.
#
# É NECESSARIO ADAPTAR ESSE ARQUIVO de makefile para suas necessidades.
#  1. Cuidado com a regra "clean" para não apagar o "support.o"
#
# OBSERVAR que as variáveis de ambiente consideram que o Makefile está no diretótio "cthread"
# 

CC=gcc
CFLAGS=-Wall -g
LIB_DIR=./lib
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src

all: escalonador.o cthread.o libcthread.a

escalonador.o: $(SRC_DIR)/escalonador.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/escalonador.c -o  $(BIN_DIR)/escalonador.o
	
cthread.o: $(SRC_DIR)/cthread.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/cthread.c -o  $(BIN_DIR)/cthread.o

libcthread.a: $(BIN_DIR)/cthread.o $(BIN_DIR)/escalonador.o $(BIN_DIR)/support.o
	ar crs $(LIB_DIR)/libcthread.a $(BIN_DIR)/cthread.o $(BIN_DIR)/escalonador.o $(BIN_DIR)/support.o

clean:
	rm -rf $(LIB_DIR)/*.a $(SRC_DIR)/*~ $(INC_DIR)/*~ *~ ; cp $(BIN_DIR)/support.o $(INC_DIR)/support.o ; rm -rf  $(BIN_DIR)/*.o ; mv $(INC_DIR)/support.o $(BIN_DIR)/support.o
