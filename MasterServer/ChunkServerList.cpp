#include "ChunkServer.h"
#include "ChunkServerList.h"

using namespace ::GFS;

ChunkServerList::ChunkServerList()
:size(0)
{
  dummy = new ChunkServer("dummy", 0);
  dummy->setPrev(dummy);
  dummy->setNext(dummy);
}  

void ChunkServerList::pushFront(ChunkServer *svc)
{
  listLink(dummy, svc, dummy->getNext());
  ++size;
}

void ChunkServerList::pushBack(ChunkServer *svc)
{
  listLink(dummy->getPrev(), svc, dummy);
  ++size;
}

void ChunkServerList::listLink(ChunkServer *prev, ChunkServer *cur, ChunkServer *next)
{
  cur->setPrev(prev);
  cur->setNext(next);
  prev->setNext(cur);
  next->setPrev(cur);
}

