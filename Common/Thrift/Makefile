.PHONY: all MasterGen ChunkGen

all: MasterGen ChunkGen

MasterGen: MasterServer.thrift
	thrift -gen cpp $<
	cp gen-cpp/MasterServer_server.skeleton.cpp ../../MasterServer/

ChunkGen: ChunkServer.thrift
	thrift -gen cpp $<
	cp gen-cpp/ChunkServer_server.skeleton.cpp ../../ChunkServer/

