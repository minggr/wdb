#ifndef WDB_PF_MANAGER_H
#define WDB_PF_MANAGER_H

#include "common.h"

typedef int PageNum;
#define ALL_PAGES -1

#define PF_OK			0
#define PF_EOF			1	// end of file
#define PF_PAGEPINNED		2	// page pinned in buffer
#define PF_PAGENOTINBUF		3	// page to be unpinned is not in buffer
#define PF_PAGEUNPINNED		4	// page already unpinned
#define PF_PAGEFREE		5	// page already free
#define PF_INVALIDPAGE		6	// invalid page number
#define PF_FILEOPEN		7	// file handle already open
#define PF_CLOSEDFILE		8	// file is closed
#define PF_ERROR		9	// file already exist

#define PF_NOMEM		-1	// out of memory
#define PF_NOBUF		-2	// out of buffer space
#define PF_INCOMPLETEREAD	-3	// incomplete read of page from file
#define PF_INCOMPLETEWRITE	-4	// incomplete write of page to file
#define PF_HDRREAD		-5	// incomplete read of header from file
#define PF_HDRWRITE		-6	// incomplete write of header to file
// Internal PF errors:
#define PF_PAGEINBUF		-7	// new allocated page already in buffer
#define PF_HASHNOTFOUND		-8	// hash table entry not found
#define PF_HASHPAGEEXIST	-9	// page already exists in hash table
#define PF_INVALIDNAME		-10	// invalid file name
#define PF_UNIX			-11	// Unix error

class PF_PageHandle {
 public:
  PF_PageHandle();
  ~PF_PageHandle();
  PF_PageHandle(const PF_PageHandle &pageHandle);
  PF_PageHandle& operator=(const PF_PageHandle &pageHandle);

  RC GetData(char *&pData) const;
  RC GetPageNum(PageNum &pageNum) const;
};

class PF_FileHandle {
 public:
  PF_FileHandle();
  ~PF_FileHandle();
  PF_FileHandle(const PF_FileHandle &pageHandle);
  PF_FileHandle& operator=(const PF_FileHandle &pageHandle);

  RC GetFirstPage(PF_PageHandle &pageHandle) const;
  RC GetLastPage(PF_PageHandle &pageHandle) const;
  RC GetNextPage(PageNum current, PF_PageHandle &pageHandle) const;
  RC GetPrevPage(PageNum current, PF_PageHandle &pageHandle) const;
  RC GetThisPage(PageNum pageNum, PF_PageHandle &pageHandle) const;

  RC AllocatePage(PF_PageHandle &pageHandle);
  RC DisposePage(PageNum pageNum);
  RC MarkDirty(PageNum pageNum) const;
  RC UnpinPage(PageNum pageNum) const;
  RC ForcePages(PageNum pageNum = ALL_PAGES) const;
};

class PF_Manager {
 public:
  PF_Manager();
  ~PF_Manager();

  RC CreateFile(const char *filename);
  RC DestroyFile(const char *filename);
  RC OpenFile(const char *filename, PF_FileHandle &fileHandle);
  RC CloseFile(PF_FileHandle &fileHandle);
  RC AllocateBlock(char *&buffer);
  RC DisposeBlock(char *buffer);
};

#endif
