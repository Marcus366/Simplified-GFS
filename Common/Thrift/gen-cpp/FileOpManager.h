/**
 * Autogenerated by Thrift Compiler (0.9.1)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef FileOpManager_H
#define FileOpManager_H

#include <thrift/TDispatchProcessor.h>
#include "Client2Master_types.h"

namespace GFS {

class FileOpManagerIf {
 public:
  virtual ~FileOpManagerIf() {}
  virtual int32_t open(const std::string& path, const int32_t oflag, const int32_t mode) = 0;
  virtual int32_t close(const int32_t fd) = 0;
  virtual void askNewChunk(FileInfo& _return, const int32_t fd) = 0;
};

class FileOpManagerIfFactory {
 public:
  typedef FileOpManagerIf Handler;

  virtual ~FileOpManagerIfFactory() {}

  virtual FileOpManagerIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(FileOpManagerIf* /* handler */) = 0;
};

class FileOpManagerIfSingletonFactory : virtual public FileOpManagerIfFactory {
 public:
  FileOpManagerIfSingletonFactory(const boost::shared_ptr<FileOpManagerIf>& iface) : iface_(iface) {}
  virtual ~FileOpManagerIfSingletonFactory() {}

  virtual FileOpManagerIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(FileOpManagerIf* /* handler */) {}

 protected:
  boost::shared_ptr<FileOpManagerIf> iface_;
};

class FileOpManagerNull : virtual public FileOpManagerIf {
 public:
  virtual ~FileOpManagerNull() {}
  int32_t open(const std::string& /* path */, const int32_t /* oflag */, const int32_t /* mode */) {
    int32_t _return = 0;
    return _return;
  }
  int32_t close(const int32_t /* fd */) {
    int32_t _return = 0;
    return _return;
  }
  void askNewChunk(FileInfo& /* _return */, const int32_t /* fd */) {
    return;
  }
};

typedef struct _FileOpManager_open_args__isset {
  _FileOpManager_open_args__isset() : path(false), oflag(false), mode(false) {}
  bool path;
  bool oflag;
  bool mode;
} _FileOpManager_open_args__isset;

class FileOpManager_open_args {
 public:

  FileOpManager_open_args() : path(), oflag(0), mode(0) {
  }

  virtual ~FileOpManager_open_args() throw() {}

  std::string path;
  int32_t oflag;
  int32_t mode;

  _FileOpManager_open_args__isset __isset;

  void __set_path(const std::string& val) {
    path = val;
  }

  void __set_oflag(const int32_t val) {
    oflag = val;
  }

  void __set_mode(const int32_t val) {
    mode = val;
  }

  bool operator == (const FileOpManager_open_args & rhs) const
  {
    if (!(path == rhs.path))
      return false;
    if (!(oflag == rhs.oflag))
      return false;
    if (!(mode == rhs.mode))
      return false;
    return true;
  }
  bool operator != (const FileOpManager_open_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FileOpManager_open_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class FileOpManager_open_pargs {
 public:


  virtual ~FileOpManager_open_pargs() throw() {}

  const std::string* path;
  const int32_t* oflag;
  const int32_t* mode;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _FileOpManager_open_result__isset {
  _FileOpManager_open_result__isset() : success(false) {}
  bool success;
} _FileOpManager_open_result__isset;

class FileOpManager_open_result {
 public:

  FileOpManager_open_result() : success(0) {
  }

  virtual ~FileOpManager_open_result() throw() {}

  int32_t success;

  _FileOpManager_open_result__isset __isset;

  void __set_success(const int32_t val) {
    success = val;
  }

  bool operator == (const FileOpManager_open_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const FileOpManager_open_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FileOpManager_open_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _FileOpManager_open_presult__isset {
  _FileOpManager_open_presult__isset() : success(false) {}
  bool success;
} _FileOpManager_open_presult__isset;

class FileOpManager_open_presult {
 public:


  virtual ~FileOpManager_open_presult() throw() {}

  int32_t* success;

  _FileOpManager_open_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _FileOpManager_close_args__isset {
  _FileOpManager_close_args__isset() : fd(false) {}
  bool fd;
} _FileOpManager_close_args__isset;

class FileOpManager_close_args {
 public:

  FileOpManager_close_args() : fd(0) {
  }

  virtual ~FileOpManager_close_args() throw() {}

  int32_t fd;

  _FileOpManager_close_args__isset __isset;

  void __set_fd(const int32_t val) {
    fd = val;
  }

  bool operator == (const FileOpManager_close_args & rhs) const
  {
    if (!(fd == rhs.fd))
      return false;
    return true;
  }
  bool operator != (const FileOpManager_close_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FileOpManager_close_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class FileOpManager_close_pargs {
 public:


  virtual ~FileOpManager_close_pargs() throw() {}

  const int32_t* fd;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _FileOpManager_close_result__isset {
  _FileOpManager_close_result__isset() : success(false) {}
  bool success;
} _FileOpManager_close_result__isset;

class FileOpManager_close_result {
 public:

  FileOpManager_close_result() : success(0) {
  }

  virtual ~FileOpManager_close_result() throw() {}

  int32_t success;

  _FileOpManager_close_result__isset __isset;

  void __set_success(const int32_t val) {
    success = val;
  }

  bool operator == (const FileOpManager_close_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const FileOpManager_close_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FileOpManager_close_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _FileOpManager_close_presult__isset {
  _FileOpManager_close_presult__isset() : success(false) {}
  bool success;
} _FileOpManager_close_presult__isset;

class FileOpManager_close_presult {
 public:


  virtual ~FileOpManager_close_presult() throw() {}

  int32_t* success;

  _FileOpManager_close_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _FileOpManager_askNewChunk_args__isset {
  _FileOpManager_askNewChunk_args__isset() : fd(false) {}
  bool fd;
} _FileOpManager_askNewChunk_args__isset;

class FileOpManager_askNewChunk_args {
 public:

  FileOpManager_askNewChunk_args() : fd(0) {
  }

  virtual ~FileOpManager_askNewChunk_args() throw() {}

  int32_t fd;

  _FileOpManager_askNewChunk_args__isset __isset;

  void __set_fd(const int32_t val) {
    fd = val;
  }

  bool operator == (const FileOpManager_askNewChunk_args & rhs) const
  {
    if (!(fd == rhs.fd))
      return false;
    return true;
  }
  bool operator != (const FileOpManager_askNewChunk_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FileOpManager_askNewChunk_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class FileOpManager_askNewChunk_pargs {
 public:


  virtual ~FileOpManager_askNewChunk_pargs() throw() {}

  const int32_t* fd;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _FileOpManager_askNewChunk_result__isset {
  _FileOpManager_askNewChunk_result__isset() : success(false) {}
  bool success;
} _FileOpManager_askNewChunk_result__isset;

class FileOpManager_askNewChunk_result {
 public:

  FileOpManager_askNewChunk_result() {
  }

  virtual ~FileOpManager_askNewChunk_result() throw() {}

  FileInfo success;

  _FileOpManager_askNewChunk_result__isset __isset;

  void __set_success(const FileInfo& val) {
    success = val;
  }

  bool operator == (const FileOpManager_askNewChunk_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const FileOpManager_askNewChunk_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FileOpManager_askNewChunk_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _FileOpManager_askNewChunk_presult__isset {
  _FileOpManager_askNewChunk_presult__isset() : success(false) {}
  bool success;
} _FileOpManager_askNewChunk_presult__isset;

class FileOpManager_askNewChunk_presult {
 public:


  virtual ~FileOpManager_askNewChunk_presult() throw() {}

  FileInfo* success;

  _FileOpManager_askNewChunk_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class FileOpManagerClient : virtual public FileOpManagerIf {
 public:
  FileOpManagerClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) :
    piprot_(prot),
    poprot_(prot) {
    iprot_ = prot.get();
    oprot_ = prot.get();
  }
  FileOpManagerClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) :
    piprot_(iprot),
    poprot_(oprot) {
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  int32_t open(const std::string& path, const int32_t oflag, const int32_t mode);
  void send_open(const std::string& path, const int32_t oflag, const int32_t mode);
  int32_t recv_open();
  int32_t close(const int32_t fd);
  void send_close(const int32_t fd);
  int32_t recv_close();
  void askNewChunk(FileInfo& _return, const int32_t fd);
  void send_askNewChunk(const int32_t fd);
  void recv_askNewChunk(FileInfo& _return);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class FileOpManagerProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<FileOpManagerIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (FileOpManagerProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_open(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_close(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_askNewChunk(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  FileOpManagerProcessor(boost::shared_ptr<FileOpManagerIf> iface) :
    iface_(iface) {
    processMap_["open"] = &FileOpManagerProcessor::process_open;
    processMap_["close"] = &FileOpManagerProcessor::process_close;
    processMap_["askNewChunk"] = &FileOpManagerProcessor::process_askNewChunk;
  }

  virtual ~FileOpManagerProcessor() {}
};

class FileOpManagerProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  FileOpManagerProcessorFactory(const ::boost::shared_ptr< FileOpManagerIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< FileOpManagerIfFactory > handlerFactory_;
};

class FileOpManagerMultiface : virtual public FileOpManagerIf {
 public:
  FileOpManagerMultiface(std::vector<boost::shared_ptr<FileOpManagerIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~FileOpManagerMultiface() {}
 protected:
  std::vector<boost::shared_ptr<FileOpManagerIf> > ifaces_;
  FileOpManagerMultiface() {}
  void add(boost::shared_ptr<FileOpManagerIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  int32_t open(const std::string& path, const int32_t oflag, const int32_t mode) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->open(path, oflag, mode);
    }
    return ifaces_[i]->open(path, oflag, mode);
  }

  int32_t close(const int32_t fd) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->close(fd);
    }
    return ifaces_[i]->close(fd);
  }

  void askNewChunk(FileInfo& _return, const int32_t fd) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->askNewChunk(_return, fd);
    }
    ifaces_[i]->askNewChunk(_return, fd);
    return;
  }

};

} // namespace

#endif
