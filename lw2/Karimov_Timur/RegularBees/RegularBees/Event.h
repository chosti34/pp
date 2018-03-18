#pragma once
#include <Windows.h>

class Event
{
public:
	Event(bool signalled);
	~Event();

	void SetSignalled();
	void SetUnsignalled();
	void WaitUntilSignalled();

private:
	HANDLE m_handle;
};
