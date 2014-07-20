CC=g++
CFLAGS=-Wall $(INCLUDE)
INCLUDE=
OBJS=ChunkServer_main.o ../MasterServer/gen-cpp/MasterServer.o \
../MasterServer/gen-cpp/MasterServer_constants.o \
../MasterServer/gen-cpp/MasterServer_types.o


%o: %cpp
	$(CC) $(CFLAGS) -c $<

ChunkServer: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ -lpthread -lthrift

.PHONY: clean

clean:
	rm ChunkServer

