.PHONY : all

all:
	(cd MasterServer && make)
	(cd ChunkServer && make)
	(cd Client && make)