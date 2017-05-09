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
SUP_DIR=./support

all: 

escalonador.o: $(SRC_DIR)/escalonador.c $(BIN_DIR)/support.o
	$(CC) $(CFLAGS) -o $(BIN_DIR)/escalonador.o $(BIN_DIR)/support.o -I$(INC_DIR) $(SRC_DIR)/escalonador.c

clean:
	rm -rf $(LIB_DIR)/*.a $(BIN_DIR)/*.o $(SRC_DIR)/*~ $(INC_DIR)/*~ *~ && cp $(SUP_DIR)/support.o $(BIN_DIR)/support.o


