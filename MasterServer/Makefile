CC=g++
CFLAGS=-Wall $(INCLUDE) -std=c++11
GENCPP=../Common/Thrift/gen-cpp
INCLUDE=-I$(GENCPP)

OBJS=ChunkServer.o ChunkServerList.o \
File.o Namespace.o \
$(GENCPP)/MasterServer.o $(GENCPP)/MasterServer_constants.o \
$(GENCPP)/MasterServer_types.o MasterServer_main.o

.PHONY: gen

%o: %cpp
	$(CC) $(CFLAGS) -c $< -o $@

mstr: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o MasterServer -lthrift

