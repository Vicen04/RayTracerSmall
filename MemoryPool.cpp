#include "MemoryPool.h"


int MemoryPool::tSlices, MemoryPool::size;
vector<Pool*> MemoryPool::mPool;
Pool MemoryPool::current;

MemoryPool::MemoryPool(size_t iObjectSize, size_t slices)
{
	phead = NULL;
	tSlices = slices;
	size = iObjectSize;
	mPool.resize(slices);
	poolSize = (iObjectSize + sizeof(Pool)) * slices;
	pMem = (char*)malloc(poolSize);
	char * temp = pMem;
	for (int i = 0; i < slices; i++)
	{
		CreateList(&phead, i, temp);
		temp += (size + sizeof(Pool));
	}
	mPool.at(0)->pNext = mPool.at(mPool.size() - 1);
	mPool.at(mPool.size() - 1)->pPrevious = mPool.at(0);
	current = *mPool.at(mPool.size() - 1);
}


MemoryPool::~MemoryPool()
{
	mPool.clear();
	free(pMem);
}

void MemoryPool::CreateList(Pool** head, int i, char* temp)
{
	mPool.at(i) = (Pool*)temp;
	mPool.at(i)->pNext = (*head);
	if ((*head) != NULL)
		(*head)->pPrevious = mPool.at(i);
	(*head) = mPool.at(i);
}

void * MemoryPool::Alloc(size_t iSize)
{
	void * pStartMemBlock = (char*)current.pNext->pPrevious + sizeof(Pool);
	current.free = false;
	for (int i = 0; i < tSlices; i++)
		if (!current.free)
			current = *current.pNext;
		else
			break;

	if (!current.free )
	{
		cout << "memory pool is full, allocating in default heap" << endl;
		return ::operator new(iSize, HeapFactory::GetDefaultHeap());
	}

	return pStartMemBlock;
}
void MemoryPool::Free(void * p, size_t iSize)
{
	for (int i = 0; i < tSlices; i++)
	{
		if ((mPool.at(i) - sizeof(Pool)) == p)
		{
			current = *mPool.at(i);
			current.free = true;
			p = nullptr;
			break;
		}
	}
}