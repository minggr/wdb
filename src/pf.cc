#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#include "pf.h"

PF_Manager::PF_Manager() {

}

PF_Manager::~PF_Manager() {

}

RC PF_Manager::CreateFile(const char *filename) {
  struct stat file_stat;

  int ret = stat(filename, &file_stat);
  if (ret != -1 || errno != ENOENT)
    return PF_ERROR;

  ret = open(filename, O_CREAT | O_RDWR, 0664);
  if (ret == -1)
    return PF_ERROR;
  close(ret);

  return PF_OK;
}

RC PF_Manager::DestroyFile(const char *filename) {
  int ret = unlink(filename);

  return ret ? PF_ERROR : PF_OK;
}
