#pragma once
#include "HeapFactory.h"

//memory manager, here are the header created to locate the memory

struct AllocHeader
{
		Heap * pHeap;
		int iSize;
		int iSignature;
		AllocHeader* pNext;
		AllocHeader* pPrevious;
};

//custom operators for the program
void * operator new (size_t size, Heap * pHeap, AllocHeader** heap);
void operator delete (void * pMem, int lock);



