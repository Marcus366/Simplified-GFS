CC=g++
CFLAGS=-Wall $(INCLUDE)
GENCPP=../Common/Thrift/gen-cpp
INCLUDE=-I$(GENCPP)
OBJS=ChunkServer_main.o $(GENCPP)/ChunkServer.o \
$(GENCPP)/ChunkServer_constants.o $(GENCPP)/ChunkServer_types.o \
$(GENCPP)/MasterServer.o $(GENCPP)/MasterServer_constants.o \
$(GENCPP)/MasterServer_types.o


%o: %cpp
	$(CC) $(CFLAGS) -c $< -o $@

ChunkServer: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ -lpthread -lthrift

.PHONY: clean

clean:
	rm ChunkServer

