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
  File* createNewFile(const std::string& path);

 private:
  File *root;
};

} //namespace GFS

#endif //__NAMESPACE_H__

