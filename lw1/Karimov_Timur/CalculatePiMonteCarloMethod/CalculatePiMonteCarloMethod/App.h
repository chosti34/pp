#pragma once
#include <Windows.h>
#include <vector>

class App
{
public:
	App();
	~App();

	float Execute(size_t iterations, size_t threads);

private:
	std::vector<HANDLE> m_hThreads;
};
