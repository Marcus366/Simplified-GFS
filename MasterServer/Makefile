CC=g++
CFLAGS=-Wall $(INCLUDE)
INCLUDE=-I../Common/Thrift/gen-cpp

GENCPP=../Common/Thrift/gen-cpp
OBJS=main.o ChunkServer.o $(GENCPP)/ChunkServerManager.o $(GENCPP)/Chunk2Master_constants.o $(GENCPP)/Chunk2Master_types.o

%o: %cpp
	$(CC) $(CFLAGS) -c $<

mstr: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $ mstr -lthrift

main.o: main.cpp ChunkServerManager_server.hpp
	$(CC) $(CFLAGS) -c $<

