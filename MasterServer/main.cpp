#include "ChunkServer.h"
#include "ChunkServerManager_server.hpp"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<ChunkServerManagerHandler> handler(new ChunkServerManagerHandler());
  shared_ptr<TProcessor> processor(new ChunkServerManagerProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

