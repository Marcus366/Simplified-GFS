CC=g++
CFLAGS=-Wall $(INCLUDE)
GENCPP=../Common/Thrift/gen-cpp
INCLUDE=-I$(GENCPP)

OBJS=MasterServer_main.o ChunkServer.o ChunkServerList.o \
File.o Namespace.o \
$(GENCPP)/MasterServer.o $(GENCPP)/MasterServer_constants.o \
$(GENCPP)/MasterServer_types.o

.PHONY: gen

%o: %cpp
	$(CC) $(CFLAGS) -c $< -o $@

mstr: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o mstr -lthrift

