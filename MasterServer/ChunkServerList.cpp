#include "ChunkServer.h"
#include "ChunkServerList.h"

using namespace ::GFS;

ChunkServerList::ChunkServerList()
{
}  


void ChunkServerList::insert(ChunkServer *svc)
{
  typedef std::unordered_map<std::string, ChunkServer*> umap;
  maps.insert(umap::value_type(svc->getIpAddr(), svc));
}

