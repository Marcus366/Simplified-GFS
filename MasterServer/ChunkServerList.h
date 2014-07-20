#ifndef __CHUNK_SERVER_LIST_H__
#define __CHUNK_SERVER_LIST_H__

#include <unordered_map>

namespace GFS {

class ChunkServer;

class ChunkServerList {
 public:
  ChunkServerList();

  void insert(ChunkServer *svc);

 private:
  std::unordered_map<std::string, ChunkServer*> maps;

};

} //namespace GFS

#endif //__CHUNK_SERVER_LIST

