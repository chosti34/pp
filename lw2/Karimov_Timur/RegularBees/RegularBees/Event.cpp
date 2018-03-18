#include "stdafx.h"
#include "Event.h"

Event::Event(bool signalled)
{
	m_handle = CreateEvent(
		NULL,
		TRUE,
		BOOL(signalled),
		NULL
	);
	assert(m_handle != NULL);
}

Event::~Event()
{
	BOOL closed = CloseHandle(m_handle);
	assert(closed);
	(void)closed;
}

void Event::SetSignalled()
{
	BOOL status = SetEvent(m_handle);
	assert(status);
	(void)status;
}

void Event::SetUnsignalled()
{
	BOOL status = ResetEvent(m_handle);
	assert(status);
	(void)status;
}

void Event::WaitUntilSignalled()
{
	DWORD status = WaitForSingleObject(m_handle, INFINITE);
	assert(status == WAIT_OBJECT_0);
	(void)status;
}
