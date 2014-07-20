CC=g++
CFLAGS=-Wall $(INCLUDE)
INCLUDE=-I../Common/Thrift/Chunk2Master/gen-cpp

CHUNK2MASTER=../Common/Thrift/Chunk2Master/gen-cpp
OBJS=main.o ChunkServer.o $(CHUNK2MASTER)/ChunkServerManager.o \
$(CHUNK2MASTER)/Chunk2Master_constants.o $(CHUNK2MASTER)/Chunk2Master_types.o

%o: %cpp
	$(CC) $(CFLAGS) -c $<

mstr: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o mstr -lthrift

main.o: main.cpp ChunkServerManager_server.hpp
	$(CC) $(CFLAGS) -c $<

