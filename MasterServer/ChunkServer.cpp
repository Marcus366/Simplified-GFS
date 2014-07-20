#include "ChunkServer.h"

using namespace ::GFS;
using namespace ::std;

ChunkServer::ChunkServer(const string &ipAddr, const int64_t totalMem)
:totalMem(totalMem)
,availMem(totalMem)
,ipAddr(ipAddr)
{
}

void ChunkServer::setIpAddr(const string &ipAddr)
{
  this->ipAddr = ipAddr;
}

string ChunkServer::getIpAddr() const
{
  return this->ipAddr;
}

void ChunkServer::addPort(int port)
{
  this->port.push_back(port);
}

int ChunkServer::getPort(unsigned int index) const
{
  return this->port[index];
}

void ChunkServer::setPrev(ChunkServer *svc)
{
  this->prev = svc;
}

void ChunkServer::setNext(ChunkServer *svc)
{
  this->next = svc;
}

ChunkServer* ChunkServer::getPrev() const
{
  return this->prev;
}

ChunkServer* ChunkServer::getNext() const
{
  return this->next;
}

