#
# Makefile para testes
# 
# Como usar:
# Bote o nome do arquivo.c em TARGET
# É isso.
#

CC=gcc
CFLAGS= -Wall -g

TARGET= T_init_escalonador

LIB_DIR=../lib
INC_DIR=../include
BIN_DIR=../bin
SRC_DIR=../src

all: $(TARGET).o $(TARGET)

$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -c $(TARGET).c

$(TARGET): $(TARGET).o $(BIN_DIR)/escalonador.o $(BIN_DIR)/support.o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o  $(BIN_DIR)/escalonador.o $(BIN_DIR)/support.o

clean:
	rm -rf *.o *~ $(TARGET)
