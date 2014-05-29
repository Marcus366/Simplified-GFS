CC = gcc
CFLAGS = -Wall $(INCLUDE)
INCLUDE = -I../include -I../rpc

%o: %c
	$(CC)  ($CFLAGS) -c $<

Client: client.o gfs_fcntl.o ../rpc/gfs_rpc_clnt.o ../rpc/gfs_rpc_xdr.o gfs_fcntl.h ../gfs_rpc.h
	$(CC) $(CFLAGS)  client.o gfs_fcntl -o ../rpc/gfs_rpc_clnt.o  ../rpc/gfs_rpc_xdr.o $@

.PHONY: clean

clean:
	rm Client