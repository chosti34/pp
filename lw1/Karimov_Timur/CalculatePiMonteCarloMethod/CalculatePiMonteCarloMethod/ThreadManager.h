#pragma once
#include <vector>
#include <Windows.h>

class ThreadManager
{
public:
	ThreadManager();
	~ThreadManager();

	void Add(LPTHREAD_START_ROUTINE callable, LPVOID lParam);
	void JoinAll();

private:
	std::vector<HANDLE> m_hThreads;
};
