#include "stdafx.h"
#include "ThreadManager.h"

ThreadManager::ThreadManager()
{
}

ThreadManager::~ThreadManager()
{
	for (auto& hThread : m_hThreads)
	{
		CloseHandle(hThread);
	}
}

void ThreadManager::Add(LPTHREAD_START_ROUTINE callable, LPVOID lParam)
{
	m_hThreads.push_back(CreateThread(NULL, 0, callable, lParam, 0, 0));
}

void ThreadManager::JoinAll()
{
	WaitForMultipleObjects(DWORD(m_hThreads.size()), m_hThreads.data(), true, INFINITE);
}
