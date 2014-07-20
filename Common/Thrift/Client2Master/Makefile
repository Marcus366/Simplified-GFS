CC=g++
CFLAGS=-Wall
OBJS=gen-cpp/Client2Master_constants.o gen-cpp/Client2Master_types.o gen-cpp/FileOpManager.o
SKELETON=FileOpManager_server.cpp

.PHONY:all

all: $(OBJS)

%o: %cpp
	$(CC) $(CFALGS) -c $< -o $@

$(SKELETON):Client2Master.thrift
	thrift -gen cpp $<

