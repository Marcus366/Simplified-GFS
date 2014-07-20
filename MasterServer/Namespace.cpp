#include "Namespace.h"

using namespace ::GFS;
using namespace ::std;

Namespace::Namespace()
{
  root = new Directory("/");
}

Namespace::~Namespace()
{
  delete root;
}

File* Namespace::findFileByPath(const string& path)
{
  return root;
}

File* Namespace::createNewFile(const string& path)
{
  size_t cut = path.rfind('/');
  string prefix = path.substr(0, cut);
  string suffix = path.substr(cut);
  File *f;
  Directory *d;

  if (cut == string::npos) {
    goto fail;
  }
  
  f = findFileByPath(prefix);
  d = dynamic_cast<Directory*>(f);
  if (d == NULL) {
    goto fail;
  }
  return d->createNewFile(suffix);
  
fail:
  return NULL;
}

