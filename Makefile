CC=gcc
CFLAGS=-Iinclude -O3 -s -DNDEBUG

lzrw3a: src/main.c src/lzrw3.c src/lzrw3-a.c
	$(CC) $(CFLAGS) -o lzrw3a src/main.c src/lzrw3.c src/lzrw3-a.c