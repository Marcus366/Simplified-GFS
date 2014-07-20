CC=g++
CFLAGS=-Wall
OBJS=gen-cpp/Chunk2Master_constants.o gen-cpp/Chunk2Master_types.o gen-cpp/ChunkServerManager.o
SKELEKON=ChunkServerManager_server.cpp

.PHONY:all

all: $(OBJS)

%o: %cpp
	$(CC) $(CFLAGS) -c $< -o $@

%cpp: Chunk2Master.thrift
	thrift -gen cpp $<

