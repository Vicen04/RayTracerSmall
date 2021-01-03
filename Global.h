#pragma once
#include "HeapFactory.h"

struct AllocHeader
{
		Heap * pHeap;
		int iSize;
		int iSignature;
		AllocHeader* pNext;
		AllocHeader* pPrevious;
};

void * operator new (size_t size, Heap * pHeap, AllocHeader** heap);
void operator delete (void * pMem, int lock);



