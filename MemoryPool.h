#pragma once
#include "Global.h"
struct Pool
{
	bool free = true;
	Pool* pNext;
	Pool* pPrevious;
};

class MemoryPool
{
public:
	MemoryPool(size_t iObjectSize, size_t slices);
	~MemoryPool();
	static void * Alloc(size_t iSize);
	static void Free(void * p, size_t iSize);
	void CreateList(Pool** head, int i, char* temp);

private:
	size_t poolSize;
	static int tSlices, size;
	char * pMem;
	static vector<Pool*> mPool;
	Pool* phead;
	static Pool current;
};

