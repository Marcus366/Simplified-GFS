#ifndef __CHUNK_SERVER_H__
#define __CHUNK_SERVER_H__

#include <string>
#include <vector>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

namespace GFS {

class ChunkServer {
 public:
  ChunkServer(const std::string &ipAddr, const int64_t totalMem);
  
  std::string getIpAddr() const;
  void setIpAddr(const std::string &ipAddr);

  void addPort(int port);
  int  getPort(unsigned int index = 0) const;

  void setPrev(ChunkServer *svc);
  void setNext(ChunkServer *svc);
  ChunkServer *getPrev() const;
  ChunkServer *getNext() const;

 private:
  int64_t totalMem, availMem;
  std::string ipAddr;
  std::vector<int> port;

  ChunkServer *prev, *next;
};

} //namespace GFS

#endif //__CHUNK_SERVER_H__

