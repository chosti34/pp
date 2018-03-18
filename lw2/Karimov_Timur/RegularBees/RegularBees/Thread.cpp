#include "stdafx.h"
#include "Thread.h"

Thread::Thread(Function&& fn)
	: m_fn(fn)
	, m_handle()
{
	m_handle = CreateThread(NULL, SIZE_T(0u), &Thread::Execute, &m_fn, DWORD(0), NULL);
	assert(m_handle != NULL);
}

Thread::~Thread()
{
	BOOL closed = CloseHandle(m_handle);
	assert(closed);
	(void)closed;
}

void Thread::Join()
{
	DWORD state = WaitForSingleObject(m_handle, INFINITE);
	assert(state == WAIT_OBJECT_0);
	(void)state;
}

DWORD WINAPI Thread::Execute(LPVOID data)
{
	auto fn = reinterpret_cast<Function*>(data);
	(*fn)();
	return 0;
}
