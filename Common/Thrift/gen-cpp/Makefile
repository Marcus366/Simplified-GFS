.PHONY: all

CC=g++
CFLAGS=-Wall $(INCLUDE)
INCLUDE=

OBJS=Chunk2Master_constants.o Chunk2Master_types.o ChunkServerManager.o

%o: %cpp
	$(CC) $(CFLAGS) -c $<

all: $(OBJS)

