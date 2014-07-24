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

void ChunkServerList::remove(ChunkServer *svc)
{
	//Hey, you can't do this
	//Add this line to push
}

void ChunServerList::removeByIpAddr(const std::string& ipAddr) 
{
	maps.erase(ipAddr);
}

ChunkServer* ChunkServerList::findByIpAddr(const std::string& ipAddr) 
{
	return maps[ipAddr];
}
