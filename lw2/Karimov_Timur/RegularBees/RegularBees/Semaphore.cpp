#include "stdafx.h"
#include "Semaphore.h"

Semaphore::Semaphore(unsigned initCount, unsigned maxCount)
{
	m_handle = CreateSemaphore(
		NULL,
		LONG(initCount),
		LONG(maxCount),
		NULL
	);
	assert(m_handle != NULL);
}

Semaphore::~Semaphore()
{
	BOOL closed = CloseHandle(m_handle);
	assert(closed);
	(void)closed;
}

void Semaphore::WaitAndLock()
{
	DWORD status = WaitForSingleObject(m_handle, INFINITE);
	assert(status == WAIT_OBJECT_0);
	(void)status;
}

void Semaphore::Release()
{
	BOOL status = ReleaseSemaphore(m_handle, LONG(1u), NULL);
	assert(status);
	(void)status;
}
