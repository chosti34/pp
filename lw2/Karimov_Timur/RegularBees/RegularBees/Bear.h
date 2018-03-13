#pragma once
#include <cstdio>
#include "Pot.h"
#include <Windows.h>

class Bear
{
public:
	Bear(Pot& pot, HANDLE* hWakeBear)
		: m_pot(pot)
		, m_wakeBear(hWakeBear)
	{
		std::printf("Hello, I'm bear\n");
	}

	void EatHoney()
	{
		while (true)
		{
			WaitForSingleObject(*m_wakeBear, INFINITE);
			m_pot.PopHoneySip();
			std::printf("Bear ate honey's sip\n");
			if (m_pot.IsEmpty())
			{
				ResetEvent(*m_wakeBear);
			}
		}
	}

private:
	Pot& m_pot;
	HANDLE* m_wakeBear;
};
