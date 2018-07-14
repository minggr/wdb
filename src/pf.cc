#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#include "pf.h"

PF_FileHandle::PF_FileHandle() {
  fd = -1;
}

PF_FileHandle::~PF_FileHandle() {
  if (fd != -1)
    close(fd);
}

PF_FileHandle& PF_FileHandle::operator=(const PF_FileHandle &pageHandle) {
  fd = pageHandle.GetFd();

  return *this;
}

int PF_FileHandle::GetFd() const {
  return fd;
}

void PF_FileHandle::SetFd(int _fd) {
  fd = _fd;
}

PF_Manager::PF_Manager() {
  pool_size = 0;

  for (int i = 0; i < kPoolSize; i++) {
    char *block = new char[kBlockSize];
    if (!block) {
      for (auto p : pool)
        delete p;
      break;
    } else {
      pool.push_back(block);
    }
  }

  pool_size = kPoolSize;
}

PF_Manager::~PF_Manager() {
  for (auto p : pool)
    delete p;
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

RC PF_Manager::OpenFile(const char *fileName, PF_FileHandle &fileHandle) {
  PF_FileHandle handle;
  int fd = fileHandle.GetFd();

  if (fd != -1)
    return PF_FILEOPEN;

  fd = open(fileName, O_RDWR);
  if (fd == -1)
    return PF_ERROR;

  handle.SetFd(fd);
  fileHandle = handle;

  return PF_OK;
}

RC PF_Manager::CloseFile(PF_FileHandle &fileHandle) {
  int fd = fileHandle.GetFd();

  if (fd == -1)
    return PF_ERROR;

  close(fd);
  return PF_OK;
}

RC PF_Manager::AllocateBlock(char *&buffer) {
  if (pool.empty()) {
    buffer = nullptr;
    return PF_NOMEM;
  }

  char *buf = pool.front();
  pool.pop_front();
  buffer = buf;

  return PF_OK;
}

RC PF_Manager::DisposeBlock(char *buffer) {
  pool.push_front(buffer);

  return PF_OK;
}
