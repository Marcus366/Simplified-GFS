.PHONY : all clean

all:
	(cd rpc && make)
	(cd MasterServer && make)
	(cd ChunkServer && make)
	(cd Client && make)

clean:
	find -name "*.o" |xargs rm
