Simplified-GFS
================================================================================

a Simplified GFS implementation

================================================================================

*Simplified-GFS* is a simplified version of *Google File System*. The paper about *GFS* is easily accessible on network. Here is one of the main paper: http://static.googleusercontent.com/media/research.google.com/zh-CN//archive/gfs-sosp2003.pdf


*GFS* makes up of one or more *Master Servers* and many of *Chunk Servers*. The *Master Server* deal with the control message, and is responsible for dispatch between *Client* and *Chunk Server*, but it is NOT interested in the data, so the data flow should not reach *Master Server* which release the *Master Server* burden so that it wiil not become the performance bottleneck.

================================================================================

*Master Server*


In more details, the *Master Server* contains the file metadata all in memory, such as the file tree and the file descriptors' mapping information. 

================================================================================

*Chunk Server*


================================================================================

*Client*


================================================================================

*RPC*


The Simplified-GFS use RPC(Remote Procedure Call) for communicate with the hosts namely clnt(client), mstr(master_server) and chk(chunk_server). If you want to know more information about RPC, you can read the document http://docs.oracle.com/cd/E19963-01/pdf/821-1671.pdf.

================================================================================

The SGFS aim to implement the POSIX's(Portable Operating System Interface for Unix) file interfaces. They are


int open(const char *path, int oflags, mode_t mode);

int close(int fd);

ssize_t read(int fd, void *buf, size_t count);

ssize_t write(int fd, const void *buf, size_t nbytes);


which is implemented in the distributed way but cover the details

================================================================================

DETAILS

OPEN

client first make a remote call OPEN. master receive the call and do:

1. Create a new node of filetree in a proper position. 

2. Init the file_t struct, make a new chunk of file_t. Then the master would pick up a chunk server, connect it and tell the chunk server open the file which name is uuid, remeber to keep the chunk fd.

3. Find the minimal unused fd(this fd is gfs level's fd, not the same as system fd), mapping it to the current file_t*, finally return the fd to client.
client receive the fd above 0, it means that OPEN is alright, maybe client will write/read later or may directly close it although it behaviour has no means.


Here we dicuss WRITE first.

client execute WRITE. We can divide the action of two parts:

1. client send fd to master and master get the fd, fd can map to file_t*, and get chunk easily because we have filt_t* now.

2. client know the message about chunk, such as chunk location and its uuid and chunk fd, then client connect the chunk server, tell the chunk server to do the system WRITE.

3. Warning: if the chunk server writing chunk is too big, the chunk server return -127 of the WRITE call and close fd, the client know it, and the client should make other call to master maybe ask_new_chunk(fd), the master flag the previous chunk close then new a chunk , return the chunk message and client do the 2nd step again.


CLOSE

CLOSE is easy. client send close message to master with fd, then master first close the chunk server,
then mark its chunk_t as close
