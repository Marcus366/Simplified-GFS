.PHONY : all clean

all:
	(cd Common && make)
	(cd MasterServer && make)
	(cd ChunkServer && make)
	(cd Client && make)

clean:
	find -name "*.o" |xargs rm
