#include "File.h"
#include <algorithm>

using namespace GFS;
using namespace std;

File::File(const string &name, mode_t mode)
:name(name)
,mode(mode)
{
}

File::~File()
{
}

const string& File::getName() const
{
  return this->name;
}

Archives::Archives(const string &name, mode_t mode)
:File(name, mode)
{
}

Archives::~Archives()
{
}

Directory::Directory(const string &name, mode_t mode)
:File(name, mode)
{
}

Directory::~Directory()
{
}

File* Directory::recursiveFindFile(const string& fullName) const
{
  File *ret = NULL;
  size_t cut = fullName.find('/');
  if (cut == string::npos) {
    ret = this->findChild(fullName);
  } else {
    string prefix = fullName.substr(0, cut);
    Directory *d = dynamic_cast<Directory*>(this->findChild(prefix));
    if (d != NULL) {
      string suffix = fullName.substr(cut + 1);
      ret = d->recursiveFindFile(suffix);
    }
  }
  return ret;
}
 
File* Directory::recursiveCreateFile(const string &fullName, mode_t mode)
{
  File *ret = NULL;
  size_t cut = fullName.find('/');
  if (cut == string::npos) {
    ret = new Archives(fullName, mode);
    this->children.push_front(ret);
  } else {
    string prefix = fullName.substr(0, cut);
    Directory *d = dynamic_cast<Directory*>(this->findChild(prefix));
    if (d != NULL) {
      string suffix = fullName.substr(cut + 1);
      ret = d->recursiveCreateFile(suffix, mode);
    }
  }
  return ret;
}

File* Directory::findChild(const string& name) const
{
  File* ret = NULL;
  list<File*>::const_iterator iter =
    std::find_if(children.begin(), children.end(), 
    [&name](File *file) {return file->getName() == name;});
  if (iter != this->children.end()) {
    ret = *iter;
  }
  return ret;
}

