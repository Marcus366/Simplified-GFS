#ifndef _FILE_H__
#define _FILE_H__

#include "Chunk.h"

#include <set>
#include <string>
#include <vector>

#include <sys/types.h>

namespace GFS {

class File {
 public:
  File(const std::string &name, mode_t mode);
  virtual ~File();

  const std::string& getName() const;

 private:
  std::string name;
  mode_t mode;
};

class Archives : public File {
 public:
  Archives(const std::string &name, mode_t mode);
  virtual ~Archives();

 private:
  /* FIXME:
   * I don't know is it std::vector is the proper container.
   * As I think, this container is used to store the Chunks
   * of a file. It just will be appended or rewrite so it 
   * has no case on deleting Chunks which is in the middle 
   * of container. As a result, std::vector is a container
   * satisfy our need.
   * However, we will support random access a file later
   * (which may be similar 'lseek' syscall). Maybe a radix
   * tree to store the Chunks will help us faster position
   * a Chunk with a exact offset.
   */
  std::vector<Chunk*> chunks;
};

class Directory : public File {
 public:
  Directory(const std::string &name, mode_t mode);
  virtual ~Directory();

  File* recursiveFindFile(const std::string& fullName) const;
  File* recursiveCreateFile(const std::string& fullName, mode_t mode);
 
  File* findChild(const std::string& name) const;
 private:
  /* FIXME:
   * Of course the std::list is bound to be a terrible container
   * to store children of a Direcotry because of its bad searching
   * performance. It is better to use balanced binary tree or B+tree
   * (while I think hash it a space waste because we have so many
   * Directories and it is all keep in memory). If you use std:set,
   * please make sure the things are ordered as you think.
   */
  std::list<File*> children;
};

} //namespace GFS

#endif //_FILE_H__

