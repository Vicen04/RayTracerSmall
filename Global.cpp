#include "Global.h"
#include <cassert>

//memory signature to locate the heap

const int MEMSYSTEM_SIGNATURE = 0xDEADC0DE;
const int MEMSYSTEM_ENDMARKER = 0xDEADBEEF;

//custom new operator with the marker
 void * operator new (size_t size, Heap * pHeap, AllocHeader** head)
{
		 size_t iRequestedBytes = size + sizeof(AllocHeader);
		 char * pMem = (char *)malloc(iRequestedBytes);
		 AllocHeader * pHeader = (AllocHeader *)pMem;
		 pHeader->pNext = (*head);
		 pHeader->iSignature = MEMSYSTEM_SIGNATURE;
		 pHeader->pHeap = pHeap;
		 pHeader->iSize = size;
		 pHeap->AddAllocation(size);
		 if ((*head) != NULL)
		 (*head)->pPrevious = pHeader;
		 (*head) = pHeader;
		
		 void * pStartMemBlock = pMem + sizeof(AllocHeader);
		 int* endMarker = (int*)((char*)pStartMemBlock + size);
		 *endMarker = MEMSYSTEM_ENDMARKER;
		 return pStartMemBlock;
}

 //custom delete operator that checks if the memory has the marker
 void operator delete (void * pMem, int lock)
{
	AllocHeader * pHeader =
		(AllocHeader *)((char *)pMem - sizeof(AllocHeader));


	if (pHeader->pHeap != NULL)
	{
		assert(pHeader->iSignature == MEMSYSTEM_SIGNATURE);
		int* endMarker = (int*)((char*)pMem + pHeader->iSize);
		assert(*endMarker == MEMSYSTEM_ENDMARKER);
		pHeader->pHeap->RemoveAllocation(pHeader->iSize);
		free(pHeader);
	}
}




