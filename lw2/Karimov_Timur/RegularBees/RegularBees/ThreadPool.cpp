#include "stdafx.h"
#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t possibleCapacity /* = 0u */)
	: m_threads()
{
	m_threads.reserve(possibleCapacity);
}

void ThreadPool::Add(Thread::Function&& fn)
{
	m_threads.push_back(std::make_unique<Thread>(std::move(fn)));
}

void ThreadPool::Join()
{
	for (auto& thread : m_threads)
	{
		thread->Join();
	}
}
