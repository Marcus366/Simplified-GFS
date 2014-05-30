CC =gcc
CFLAGS =-Wall $(INCLUDE)
INCLUDE =-I../include -I../rpc

OBJS =gfs_mstr.o file.o filetree.o gfs_chk.o gfs_list.o

%o: %c
	$(CC) $(CFLAGS) -c $<


mstr: $(OBJS) ../include/gfs.h ../rpc/gfs_rpc.h
	$(CC) $(CFLAGS) $(OBJS) -o $ mstr

.PHONY: clean

clean:
	find -name "*.o" |xargs rm
