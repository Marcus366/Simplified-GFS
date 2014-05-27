.PHONY : all

all:
	(cd MasterServer && make)
	(cd Client && make)