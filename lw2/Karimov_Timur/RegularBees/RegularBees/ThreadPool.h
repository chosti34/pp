#pragma once
#include "Thread.h"
#include <vector>
#include <memory>

class ThreadPool
{
public:
	ThreadPool(size_t possibleCapacity = 0u);

	void Add(Thread::Function&& fn);
	void Join();

private:
	std::vector<std::unique_ptr<Thread>> m_threads;
};
