#include <unistd.h>
#include <sys/time.h>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "../MasterServer/gen-cpp/MasterServer.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace GFS;

using namespace boost;

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
 
