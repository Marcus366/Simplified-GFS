.PHONY: all MasterGen

CHUNK_SERVER_MANAGER=ChunkServerManager_server.skeleton.cpp
FILE_OP_MANAGER=FileOpManager_server.skeleton.cpp
FILE_IO=FileIO_server.skeleton.cpp


all: MasterGen

MasterGen: MasterServer.thrift
	thrift -gen cpp MasterServer.thrift
	cp gen-cpp MasterServer_server.skeleton.cpp ../../MasterServer/

