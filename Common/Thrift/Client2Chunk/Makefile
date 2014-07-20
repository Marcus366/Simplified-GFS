CC=g++
CFLAGS=-Wall
OBJS=gen-cpp/Client2Chunk_constants.o gen-cpp/Client2Chunk_types.o gen-cpp/FileIO.o
SKELETON=FileIO_server.cpp

.PHONY:all

all: $(OBJS)

%o: %cpp
	$(CC) $(CFALGS) -c $< -o $@

$(SKELETON): Client2Chunk.thrift
	thrift -gen cpp $<

