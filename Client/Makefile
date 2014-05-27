CC = gcc
CFLAGS = -Wall $(INCLUDE)
INCLUDE = -I../include

Client: client.c ../include/gfs.h
	$(CC) $(CFLAGS) $< -o $ Client

.PHONY: clean

clean:
	rm Client