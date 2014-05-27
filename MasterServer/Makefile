CC = gcc
CFLAGS = -Wall $(INCLUDE)
INCLUDE = -I../include

MasterServer: master.c ../include/gfs.h
	$(CC) $(CFLAGS) $< -o $ MasterServer

.PHONY: clean

clean:
	rm MasterServer