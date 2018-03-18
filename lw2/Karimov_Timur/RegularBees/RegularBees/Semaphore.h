#pragma once
#include <Windows.h>

class Semaphore
{
public:
	Semaphore(unsigned initCount, unsigned maxCount);
	~Semaphore();

	void WaitAndLock();
	void Release();

private:
	HANDLE m_handle;
};
