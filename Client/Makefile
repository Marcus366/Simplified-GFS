CC = gcc
CFLAGS = -Wall $(INCLUDE)
INCLUDE = -I../include -I../rpc

OBJS =gfs_clnt.o gfs_fcntl.o rpc_clnt.o ../rpc/gfs_rpc_xdr.o

%o: %c
	$(CC) $(CFLAGS) -c $<

client: $(OBJS) gfs_clnt.h gfs_fcntl.h ../include/gfs_rpc.h
	$(CC) $(CFLAGS)  $(OBJS) -o $@

rpc_clnt.o: rpc_clnt.o ../rpc/gfs_rpc.h
	$(CC) $(CFLAGS) -c $<


.PHONY: clean

clean:
	rm client
	find -name "*.o" |xargs rm