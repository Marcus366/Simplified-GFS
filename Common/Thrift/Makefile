.PHONY: all

CHUNK_SERVER_MANAGER=ChunkServerManager_server.skeleton.cpp
FILE_OP_MANAGER=FileOpManager_server.skeleton.cpp
FILE_IO=FileIO_server.skeleton.cpp

all:
	(cd Chunk2Master && make)
	(cd Client2Chunk && make)
	(cd Client2Master && make)
	cp Chunk2Master/gen-cpp/$(CHUNK_SERVER_MANAGER) ../../MasterServer/$(CHUNK_SERVER_MANAGER)
	cp Client2Master/gen-cpp/$(FILE_OP_MANAGER) ../../MasterServer/$(FILE_OP_MANAGER)
	cp Client2Chunk/gen-cpp/$(FILE_IO) ../../ChunkServer/$(FILE_IO)

