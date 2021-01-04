#include "HeapFactory.h"

//heaps created, it also checks and locks the program in case this is run in multiple threads to make sure the count is correct

std::vector<Heap*> HeapFactory::heaps;
mutex HeapFactory::locked;

HeapFactory::HeapFactory()
{
}


HeapFactory::~HeapFactory()
{
	heaps.clear();
}

Heap* HeapFactory::CreateHeap(const char* szName)
{
	locked.lock();
	Heap* heap = GetHeap(szName);
	if (heap == heaps.at(0))
	{
		heap = new Heap(szName);
		heaps.push_back(heap);
		std::cout << "heap " << szName << " created" << std::endl;
	}
	locked.unlock();
      return heap;
}

void HeapFactory::CreateDefaultHeap()
{
	if (heaps.size() < 1)
	{
		heaps.push_back((Heap*)malloc(sizeof(Heap("default"))));
		std::cout << "default heap created" <<  std::endl;
	}
}

Heap*	HeapFactory::GetDefaultHeap()
{ 
	if(heaps.size() > 0)
		return heaps.at(0);
}

Heap* HeapFactory::GetHeap(const char* szName)
{
	int i = 0;
	int j = 1;
	for (; i < heaps.size(); i++)
	{
		if(heaps.at(i) != NULL)
		if (heaps.at(i)->getName()[0] == szName[0])
		{
			for (; j < strlen(szName); j++)
			{
				if (heaps.at(i)->getName()[j] != szName[j])
					break;
			}
			if (j >= strlen(szName))
			{
				std::cout << szName << std::endl;
				return heaps.at(i);
			}
		}
	}
	std::cout << "couldn't find heap" << std::endl;
	return heaps.at(0);
}