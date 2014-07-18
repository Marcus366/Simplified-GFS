.PHONY: all

THRIFT_FILES=Chunk2Master.thrift Client2Chunk.thrift Client2Master.thrift
CHUNK_SERVER_MANAGER=ChunkServerManager_server.skeleton.cpp
FILE_OP_MANAGER=FileOpManager_server.skeleton.cpp
FILE_IO=FileIO_server.skeleton.cpp
THRIFT=thrift -gen cpp

all:
	$(THRIFT) Chunk2Master.thrift
	$(THRIFT) Client2Chunk.thrift
	$(THRIFT) Client2Master.thrift
	cp gen-cpp/$(CHUNK_SERVER_MANAGER) ../../MasterServer/$(CHUNK_SERVER_MANAGER)
	cp gen-cpp/$(FILE_OP_MANAGER) ../../MasterServer/$(FILE_OP_MANAGER)
	cp gen-cpp/$(FILE_IO) ../../ChunkServer/$(FILE_IO)
	(cd gen-cpp && make)

