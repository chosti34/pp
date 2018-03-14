#pragma once
#include <cstdio>
#include "Pot.h"
#include <Windows.h>
#include <cassert>

class Bear
{
public:
	Bear(Pot& pot, HANDLE* hWakeBear, HANDLE* noBeesPuttingHoney)
		: m_pot(pot)
		, m_wakeBear(hWakeBear)
		, m_noBeesPuttingHoney(noBeesPuttingHoney)
	{
		std::printf("Hello, I'm bear\n");
	}

	void EatHoney()
	{
		while (true)
		{
			WaitForSingleObject(*m_wakeBear, INFINITE);
			m_pot.PopHoneySip();
			std::printf("Nom-nom-nom! (Bear ate honey's sip)\n");
			if (m_pot.IsEmpty())
			{
				ResetEvent(*m_wakeBear);
				LONG value;
				BOOL b = ReleaseSemaphore(*m_noBeesPuttingHoney, 1u, &value);
				assert(b);
				printf("%d\n", value);
			}
		}
	}

private:
	Pot& m_pot;
	HANDLE* m_wakeBear;
	HANDLE* m_noBeesPuttingHoney;
};
