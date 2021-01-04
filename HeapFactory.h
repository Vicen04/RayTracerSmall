#pragma once
#include "Heap.h"
#include <iostream>
#include <vector>

//self explanatory

class Heap;

class HeapFactory
{
public:
	HeapFactory();
	~HeapFactory();
	static Heap* 	CreateHeap(const char* szName);
	static void		CreateDefaultHeap();
	static Heap*	GetDefaultHeap(); 
	static Heap*	GetHeap(const char* szName);

private:
	static std::vector<Heap*> heaps;
	//used to make sure there are no errors while being in different threads
	static mutex locked;
};

