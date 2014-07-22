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

Build-Dep: Thrift-v0.9.1

The Simplified-GFS use RPC(Remote Procedure Call) for communicate with MasterServer, ChunkServer and Client. 

================================================================================

The SGFS aim to implement the POSIX's(Portable Operating System Interface for Unix) file interfaces. They are

_open_, _close_, _read_, _write_

which is implemented in the distributed way but cover the details

(Maybe we will implement many other interface with many other languages)

================================================================================

