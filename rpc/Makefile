CC =gcc
LD =ld
CFLAGS =-Wall
RPC_OBJS =gfs_rpc_xdr.o

.PHONY: all

#all: gfs_rpc_clnt.o gfs_rpc_srv.o
#all: gfs_rpc_clnt.o gfs_rpc_svc.o gfs_rpc_xdr.o

%o: %c
	$(CC) $(CFLAGS) -c $<

all: gen/gfs_rpc.x $(RPC_OBJS)
	rpcgen gen/gfs_rpc.x
	cp gen/gfs_rpc.h ./
	cp gen/gfs_rpc_xdr.c ./ 


#client: client.c gfs_rpc.h gfs_rpc_xdr.c gfs_rpc_clnt.c
#	$(CC) $(CFLAGS) client.c gfs_rpc_clnt.c -o client

#server: server.c gfs_rpc.h gfs_rpc_xdr.c gfs_rpc_svc.c
#	$(CC) $(CFLAGS) server.c gfs_rpc_svc.c -o server

#gfs_rpc_clnt.o: gfs_rpc_clnt.o gfs_rpc_xdr.o
#	$(LD) gfs_rpc_clnt.o gfs_rpc_xdr.o -o gfs_rpc_clnt.o

#gfs_rpc_srv.o: gfs_rpc_svc.o gfs_rpc_xdr.o
#	$(LD) -gfs_rpc_svc.o gfs_rpc_xdr.o -o gfs_rpc_srv.o
