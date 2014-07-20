#ifndef _FILE_H__
#define _FILE_H__

#include <string>
#include <set>

namespace GFS {

class File {
 public:
  File(const std::string &name);
  virtual ~File();

 private:
  std::string name;
};

class Archives : public File {
 public:
  Archives(const std::string &name);
  virtual ~Archives();
};

class Directory : public File {
 public:
  Directory(const std::string &name);
  virtual ~Directory();

  File* createNewFile(const std::string& name);
 
 private:
  std::set<File*> children;
};

} //namespace GFS

#endif //_FILE_H__
