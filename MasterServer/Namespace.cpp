#include "Namespace.h"

using namespace ::GFS;

Namespace::Namespace()
{
  root = new File("/", FileType_Directory);
}

Namespace::~Nameapce()
{
  delete root;
}

File* Namespace::findByPath(const std::string& path)
{
  return root;
}

File* Namespace::createNewFile(const std::string& path)
{
  size_t cut = path.rfind('/');
  if (cut == string::npos) {
    goto fail;
  }
  string prefix = path.substr(path, cut);
  string suffix = path.substr(cut);
  
  File *f = fileByPath(prefix);
  Directory *d = dynamic_cast<Directory*>(f);
  if (d == NULL) {
    goto fail;
  }
  return d->createNewFile(suffix);
  
fail:
  return NULL;
}

