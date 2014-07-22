#include "Namespace.h"

using namespace ::GFS;
using namespace ::std;

Namespace::Namespace()
{
  root = new Directory("/", 0);
}

Namespace::~Namespace()
{
  delete root;
}

File* Namespace::findFileByPath(const string& path)
{
  //TODO: Here should add some code checking the path whether is legal.
  return root->recursiveFindFile(path);
}

File* Namespace::createNewFile(const string& path, mode_t mode)
{
  //TODO: Here should add some code checking the path whether is legal.
  return root->recursiveCreateFile(path, mode);
}

