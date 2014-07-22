#ifndef __NAMESPACE_H__
#define __NAMESPACE_H__

#include "File.h"

#include <list>
#include <string>

namespace GFS {

class Namespace {
 public:
  Namespace();
  ~Namespace();

  File* findFileByPath(const std::string& path);
  File* createNewFile(const std::string& path, mode_t mode);

  Directory* createDirectory(const std::string& path, mode_t mode);
 private:
  Directory *root;
};

} //namespace GFS

#endif //__NAMESPACE_H__

