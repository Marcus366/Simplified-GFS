CC = gcc

jb: linkListTest.c ../MasterServer/linklist.h ../MasterServer/linklist.c ../MasterServer/linklist.o
	$(CC) $< ../MasterServer/linklist.o -o jb

../MasterServer/linklist.o: ../MasterServer/linklist.c ../MasterServer/linklist.h
	$(CC) -c ../MasterServer/linklist.c -o ../MasterServer/linklist.o

 
