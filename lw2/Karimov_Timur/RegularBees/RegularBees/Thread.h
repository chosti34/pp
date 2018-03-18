#pragma once
#include <Windows.h>
#include <functional>
#include <boost/noncopyable.hpp>

class Thread : private boost::noncopyable
{
public:
	using Function = std::function<void()>;

	Thread(Function&& fn);
	~Thread();

	void Join();

private:
	static DWORD WINAPI Execute(LPVOID data);

	Function m_fn;
	HANDLE m_handle;
};
