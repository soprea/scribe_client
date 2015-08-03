CURRENT_DIR = $(shell pwd)
COMPILE_DIR = $(CURRENT_DIR)/../

CFLAGS = -fPIC -g -pipe
LDFLAGS = -L$(COMPILE_DIR) -lscribe_utils -lmysqlclient -lpthread -lz -lm -ldl
INCLUDES = -I$(COMPILE_DIR) -DBIG_JOINS=1  -fno-strict-aliasing   -g -DNDEBUG

CC = gcc

all: scribe

scribe:
	$(CC) scribe_client.c $(CFLAGS)  $(LDFLAGS) $(INCLUDES) -o scribe_client

run:	
	LD_LIBRARY_PATH=$(COMPILE_DIR) ./scribe_client localhost 1463 test test

clean: 
	rm -f *.o scribe_client

