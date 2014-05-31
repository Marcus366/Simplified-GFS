CC =gcc
CFLAGS =-Wall $(INCLUDE)
INCLUDE =-I../include -I../rpc

OBJS =gfs_mstr_svc.o rpc_mstr.o gfs_list.o ../rpc/gfs_rpc_xdr.o

%o: %c
	$(CC) $(CFLAGS) -c $<


mstr: $(OBJS) ../include/gfs.h ../rpc/gfs_rpc.h
	$(CC) $(CFLAGS) $(OBJS) -o $ mstr
