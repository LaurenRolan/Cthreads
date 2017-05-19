#
# Makefile para testes
# 
# Gera todos testes das pastas

CC=gcc
CFLAGS= -Wall

LIB_DIR=../lib
BIN_DIR=../bin

all: T_cidentify T_ccreate T_cjoin2 T_cjoin T_csem_init T_csetprio T_csignal T_cwait T_cyield T_dispatcher T_free_blocked_by T_init_escalonador T_init_lib T_put_aptos T_search_thread T_terminate_thread

T_cidentify: T_cidentify.c $(LIB_DIR)/libcthread.a
	$(CC) -o T_cidentify T_cidentify.c -L$(LIB_DIR) -lcthread $(CFLAGS)

T_ccreate: T_ccreate.c $(LIB_DIR)/libcthread.a
	$(CC) -o T_ccreate T_ccreate.c -L$(LIB_DIR) -lcthread $(CFLAGS)

T_cjoin2: T_cjoin2.c $(LIB_DIR)/libcthread.a
	$(CC) -o T_cjoin2 T_cjoin2.c -L$(LIB_DIR) -lcthread $(CFLAGS)

T_cjoin: T_cjoin.c $(LIB_DIR)/libcthread.a
	$(CC) -o T_cjoin T_cjoin.c -L$(LIB_DIR) -lcthread $(CFLAGS)

T_csem_init: T_csem_init.c $(LIB_DIR)/libcthread.a
	$(CC) -o T_csem_init T_csem_init.c -L$(LIB_DIR) -lcthread $(CFLAGS)

T_csetprio: T_csetprio.c $(LIB_DIR)/libcthread.a
	$(CC) -o T_csetprio T_csetprio.c -L$(LIB_DIR) -lcthread $(CFLAGS)

T_csignal: T_csignal.c $(LIB_DIR)/libcthread.a
	$(CC) -o T_csignal T_csignal.c -L$(LIB_DIR) -lcthread $(CFLAGS)

T_cwait: T_cwait.c $(LIB_DIR)/libcthread.a
	$(CC) -o T_cwait T_cwait.c -L$(LIB_DIR) -lcthread $(CFLAGS)

T_cyield: T_cyield.c $(LIB_DIR)/libcthread.a
	$(CC) -o T_cyield T_cyield.c -L$(LIB_DIR) -lcthread $(CFLAGS)

T_dispatcher: T_dispatcher.c $(LIB_DIR)/libcthread.a
	$(CC) -o T_dispatcher T_dispatcher.c -L$(LIB_DIR) -lcthread $(CFLAGS)

T_free_blocked_by: T_free_blocked_by.c $(LIB_DIR)/libcthread.a
	$(CC) -o T_free_blocked_by T_free_blocked_by.c -L$(LIB_DIR) -lcthread $(CFLAGS)

T_init_escalonador: T_init_escalonador.c $(LIB_DIR)/libcthread.a
	$(CC) -o T_init_escalonador T_init_escalonador.c -L$(LIB_DIR) -lcthread $(CFLAGS)

T_init_lib: T_init_lib.c $(LIB_DIR)/libcthread.a
	$(CC) -o T_init_lib T_init_lib.c -L$(LIB_DIR) -lcthread $(CFLAGS)

T_put_aptos: T_put_aptos.c $(LIB_DIR)/libcthread.a
	$(CC) -o T_put_aptos T_put_aptos.c -L$(LIB_DIR) -lcthread $(CFLAGS)

T_search_thread: T_search_thread.c $(LIB_DIR)/libcthread.a
	$(CC) -o T_search_thread T_search_thread.c -L$(LIB_DIR) -lcthread $(CFLAGS)

T_terminate_thread: T_terminate_thread.c $(LIB_DIR)/libcthread.a
	$(CC) -o T_terminate_thread T_terminate_thread.c -L$(LIB_DIR) -lcthread $(CFLAGS)

clean:
	rm -rf *.o *~ T_cidentify T_ccreate T_cjoin2 T_cjoin T_csem_init T_csetprio T_csignal T_cwait T_cyield T_dispatcher T_free_blocked_by T_init_escalonador T_init_lib T_put_aptos T_search_thread T_terminate_thread
