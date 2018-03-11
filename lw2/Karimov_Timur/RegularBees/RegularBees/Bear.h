#pragma once
#include <cstdio>

class Bear
{
public:
	Bear()
		: m_isSleeping(false)
	{
		std::printf("Hello, I'm bear");
	}

private:
	bool m_isSleeping;
};
