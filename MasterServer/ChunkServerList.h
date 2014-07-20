#ifndef __CHUNK_SERVER_LIST_H__
#define __CHUNK_SERVER_LIST_H__


namespace GFS {

class ChunkServer;

class ChunkServerList {
 public:
  ChunkServerList();

  void pushFront(ChunkServer *svc);
  void pushBack(ChunkServer *svc);

  void What(ChunkServer *svc) {
    ; //do nothing
  }

 private:
  int size;
  ChunkServer *dummy;

  static void listLink(ChunkServer *prev, ChunkServer *cur, ChunkServer *next);
};

} //namespace GFS

#endif //__CHUNK_SERVER_LIST

