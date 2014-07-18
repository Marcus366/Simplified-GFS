#include "ChunkServer.h"
#include "Chunk2Master_constants.h"
#include "Chunk2Master_types.h"
#include "ChunkServerManager.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::GFS;

class ChunkServerManagerHandler : virtual public ChunkServerManagerIf {
 private:
//  static ChunkServerList chunkServers;

 public:
  ChunkServerManagerHandler() {
    // Your initialization goes here
  }

  bool registerChunkServer(const std::string& ipAddr, const int64_t availMem) {
    ChunkServer *svc = new ChunkServer(ipAddr, availMem);
 //   chunkServers.pushFront(svc);
    printf("registerChunkServer %s\n", ipAddr.c_str());
    return true;
  }

  void unregisterChunkServer(const std::string& ipAddr) {
    // Your implementation goes here
    printf("unregisterChunkServer\n");
  }

  bool heartBeat(const ChunkServerInfo& info) {
    // Your implementation goes here
    printf("heartBeat\n");
    return true;
  }

};

