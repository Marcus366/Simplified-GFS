#include "ChunkServer.h"
#include "ChunkServerList.h"
#include "MasterServer.h"
#include "Namespace.h"

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include <unistd.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::GFS;

class MasterServerHandler : virtual public MasterServerIf {
 private:
  static ChunkServerList chunkServers;
  static Namespace       root;

 public:
  MasterServerHandler() {
  }

  bool registerChunkServer(const std::string& ipAddr, const int64_t availMem) {
    ChunkServer *svc = new ChunkServer(ipAddr, availMem);
    chunkServers.pushFront(svc);
    printf("registerChunkServer\n");
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

  int32_t open(const std::string& path, const int32_t oflag, const int32_t mode) {
    if (mode & O_CREAT) {
      root.createNewFile(path);
    }
    printf("open\n");
    return 0;
  }

  int32_t close(const int32_t fd) {
    // Your implementation goes here
    printf("close\n");
    return 0;
  }

  void askNewChunk(FileInfo& _return, const int32_t fd) {
    // Your implementation goes here
    printf("askNewChunk\n");
  }

};

ChunkServerList MasterServerHandler::chunkServers;
Namespace       MasterServerHandler::root;

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<MasterServerHandler> handler(new MasterServerHandler());
  shared_ptr<TProcessor> processor(new MasterServerProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

