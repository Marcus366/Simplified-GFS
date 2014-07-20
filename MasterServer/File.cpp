#include "File.h"

using namespace GFS;
using namespace std;

File::File(const string &name)
:name(name)
{
}

File::~File()
{
}

Archives::Archives(const string &name)
:File(name)
{
}

Archives::~Archives()
{
}

Directory::Directory(const string &name)
:File(name)
{
}

Directory::~Directory()
{
}

File* Directory::createNewFile(const string &name)
{
  Archives *f = new Archives(name);
  children.insert(f);
  return f;
}

