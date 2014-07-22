#ifndef _CHUNK_H__
#define _CHUNK_H__

#include "ChunkServer.h"

namespace GFS {

class Chunk {
 public:
  Chunk() {
  }

 private:
  ChunkServer *server;
  std::string uuid;
  int         chkfd;
};

} //namespace GFS

#endif //_CHUNK_H__
