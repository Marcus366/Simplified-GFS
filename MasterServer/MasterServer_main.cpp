#include "Macros.h"
#include "ChunkServer.h"
#include "ChunkServerList.h"
#include "MasterServer.h"
#include "Namespace.h"

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include <unistd.h>
#include <fcntl.h>

#include <bitset>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;
using std::bitset;

using namespace  ::GFS;

class MasterServerHandler : virtual public MasterServerIf {
 private:
  static ChunkServerList chunkServers;
  static Namespace       root;

  static bitset<1024>    fds;
 public:
  MasterServerHandler() {
  }

  bool registerChunkServer(const std::string& ipAddr, const int64_t availMem) {
    ChunkServer *svc = new ChunkServer(ipAddr, availMem);
    chunkServers.insert(svc);
    printf("registerChunkServer\n");
    return true;
  }

  void unregisterChunkServer(const std::string& ipAddr) {
    // Your implementation goes here
    chunkServers.removeByIpAddr(ipAddr);
    //My implementation ends here
    printf("unregisterChunkServer\n");
  }

  bool heartBeat(const ChunkServerInfo& info) {
    // Your implementation goes here
    printf("heartBeat\n");
    return true;
  }

  int32_t open(const std::string& path, const int32_t oflag, const int32_t mode) {
    File *file = NULL;
    if (mode & O_CREAT) {
      file = root.createNewFile(path, mode);
    } else {
      file = root.findFileByPath(path);
    }
    UNUSED(file);
    printf("open\n");
    return getFD();
  }

  int32_t close(const int32_t fd) {
    // Your implementation goes here
    //You need a function like findFileByFd() in namespace.cpp!
    //And where is File.h, I cannot find it
    printf("close\n");
    return 0;
  }

  void askNewChunk(FileInfo& _return, const int32_t fd) {
    // Your implementation goes here
    printf("askNewChunk\n");
  }

 private:
  int getFD() {
    int fd = 0;
    while (fd < 1024 && !fds.test(fd)) {
      ++fd;
    }
    if (fd < 1024) {
      fds.set(fd);
    } else {
      fd = -1;
    }
    return fd;
  }
};

ChunkServerList MasterServerHandler::chunkServers;
Namespace       MasterServerHandler::root;
bitset<1024>    MasterServerHandler::fds;

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

