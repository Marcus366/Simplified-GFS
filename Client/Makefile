CC = gcc
CFLAGS = -Wall $(INCLUDE)
INCLUDE = -I../include -I../rpc

OBJS =gfs_clnt.o gfs_fcntl.o rpc_clnt.o ../rpc/gfs_rpc_xdr.o

%o: %c
	$(CC) $(CFLAGS) -c $<

all: rpc_clnt.o test

rpc_clnt.o: rpc_clnt.c ../rpc/gfs_rpc.h
	$(CC) $(CFLAGS) -c $<


.PHONY: all clean test

test: write_file_test read_console_test write_console_test

write_file_test: ../test/write_file_test.c $(OBJS)
	$(CC) $(FLAGS) $< $(OBJS) -o ../test/write_file_test

write_console_test: ../test/write_console_test.c $(OBJS)
	$(CC) $(FLAGS) $< $(OBJS) -o ../test/write_console_test

read_console_test: ../test/read_console_test.c $(OBJS)
	$(CC) $(FLAGS) $< $(OBJS) -o ../test/read_console_test

clean:
	rm client
