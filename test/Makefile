CURRENT_DIR = $(shell pwd)
COMPILE_DIR = $(CURRENT_DIR)/../

CFLAGS = -fPIC -g -pipe -m64
LDFLAGS = -L$(COMPILE_DIR) -lscribe_utils -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lz -lm -ldl
INCLUDES = -I$(COMPILE_DIR) -I/usr/include/mysql -DBIG_JOINS=1  -fno-strict-aliasing   -g -DNDEBUG

CC = gcc

all: scribe arduino-serial-daemon arduino-serial-daemon-nosql

arduino-serial-daemon-nosql:
	$(CC) arduino-serial-daemon-nosql.c arduino-serial-lib-daemon.c $(CFLAGS)  $(LDFLAGS) $(INCLUDES) -o arduino-serial-daemon-nosql

arduino-serial-daemon:
	$(CC) arduino-serial-daemon.c arduino-serial-lib-daemon.c $(CFLAGS)  $(LDFLAGS) $(INCLUDES) -o arduino-serial-daemon

scribe:
	$(CC) scribe_client.c $(CFLAGS)  $(LDFLAGS) $(INCLUDES) -o scribe_client

run:	
	LD_LIBRARY_PATH=$(COMPILE_DIR) ./scribe_client localhost 1463 test test

clean: 
	rm -f *.o scribe_client arduino-serial-daemon arduino-serial-daemon-nosql

