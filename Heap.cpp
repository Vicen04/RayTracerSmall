#include "Heap.h"
#include <string.h>


Heap::Heap(const char * name)
{
	strncpy_s(m_name, name , strlen(name));
}


Heap::~Heap()
{
}

void Heap::AddAllocation(size_t size)
{
	m_allocatedBytes += size;
}

void Heap::RemoveAllocation(size_t size)
{
	m_allocatedBytes -= size;
}
