#pragma once
#include <mutex>
#include <thread>
#include <ppltasks.h>
#include <concurrent_vector.h>

using namespace concurrency;
using namespace std;

class ThreadManager
{
public:
	ThreadManager();
	~ThreadManager();	
};

