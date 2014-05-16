CC=gcc
CFLAGS=-g -Os -DLANGUAGE=ENGLISH -Wall -Wextra -pedantic -std=gnu99
INC=-Iinclude
LDFLAGS=

all:
	$(CC) $(INC) $(CFLAGS) src/pfhor.c -c
	$(CC) $(INC) $(CFLAGS) src/grepline.c -c
	$(CC) $(INC) $(CFLAGS) src/readreport.c -c
	$(CC) $(INC) $(CFLAGS) src/endian.c -c
	$(CC) $(INC) $(CFLAGS) src/dumpmem.c -c
	$(CC) $(CFLAGS) $(LDFLAGS) pfhor.o dumpmem.o grepline.o readreport.o endian.o -o main

clean:
	rm -f *.o main
