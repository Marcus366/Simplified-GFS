#include "ChunkServer.h"
#include "MasterServer.h"

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;
using std::string;

using namespace  ::GFS;

class ChunkServerHandler : virtual public ChunkServerIf {
 public:
  ChunkServerHandler() {
  }

  int32_t open(const string& path, const int32_t oflag, const int32_t mode) {
    printf("open %s\n", path.c_str());
    return ::open(path.c_str(), oflag, mode);
  }

  int32_t close(const int32_t fd) {
    printf("close %d\n", fd);
    return ::close(fd);
  }

  int64_t write(const int32_t fd, const string& buf, const int32_t count) {
    printf("write\n");
    return ::write(fd, buf.c_str(), count);
  }


  void read(ReadResult& _return, const int32_t fd, const int32_t count) {
    printf("read\n");
    void* buf = malloc(count);
    if (buf == NULL) {
      _return.count = -1;
    } else {
      _return.count = ::read(fd, buf, count);
      _return.buf.assign((const char*)buf, sizeof(_return.count));
      free(buf);
    }
  }

};

int main(int argc, char **argv) {
  shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
  shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  MasterServerClient client(protocol);

  transport->open();
  client.registerChunkServer("127.0.0.1", 1000);
  transport->close();


  int port = 9091;
  shared_ptr<ChunkServerHandler> handler(new ChunkServerHandler());
  shared_ptr<TProcessor> processor(new ChunkServerProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

/*
int main(int argc, char** argv)
{
  shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
  shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  MasterServerClient client(protocol);

  transport->open();
  client.registerChunkServer("127.0.0.1", 1000);
  transport->close();
}
*/

