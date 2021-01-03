#pragma once
#include <stdlib.h>
#include "ThreadManager.h"

class Heap
{
public:
	Heap(const char * name);
	~Heap();
	void AddAllocation(size_t size);
	void RemoveAllocation(size_t size);
	size_t TotalAllocation() { return m_allocatedBytes; }
	const char * getName() const { return m_name; }

private:
	size_t	m_allocatedBytes = 0;
	char m_name[20];
};

