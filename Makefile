CC=gcc
CFLAGS=-g -Os -DLANGUAGE=ENGLISH -Wall -Wextra -pedantic -std=gnu99
INC=-Iinclude -I../grepline
LDFLAGS=
grepline:
	$(CC) $(CFLAGS) ../grepline/grepline.c -c

all:	grepline
	$(CC) $(INC) $(CFLAGS) src/main.c -c
	$(CC) $(INC) $(CFLAGS) src/readreport.c -c
	$(CC) $(INC) $(CFLAGS) src/endian.c -c
	$(CC) $(INC) $(CFLAGS) src/dumpmem.c -c
	$(CC) $(CFLAGS) $(LDFLAGS) grepline.o main.o dumpmem.o readreport.o endian.o -o main

dumper:	all
	$(CC) $(INC) $(CFLAGS) src/example-dump.c -c
	$(CC) $(CFLAGS) $(LDFLAGS) grepline.o example-dump.o dumpmem.o readreport.o endian.o -o dumper

clean:
	rm -f *.o main
