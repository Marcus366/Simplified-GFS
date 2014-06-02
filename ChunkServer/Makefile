CC = gcc
CFLAGS = -Wall $(INCLUDE)
INCLUDE = -I../include
OBJS =gfs_chk_svc.o rpc_chk.o ../rpc/gfs_rpc_xdr.o

%o: %c
	$(CC) $(CFLAGS) -c $<

chk: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

.PHONY: clean

clean:
	rm chk
