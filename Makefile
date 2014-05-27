.PHONY : all clean

all:
	(cd MasterServer && make)
	(cd ChunkServer && make)
	(cd Client && make)

clean:
	(cd MasterServer && make clean)
	(cd ChunkServer && make clean)
	(cd Client && make clean)
