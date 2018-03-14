#pragma once
#include <cstdio>
#include "Pot.h"
#include <Windows.h>

class Bee
{
public:
	Bee(unsigned id, Pot& pot, HANDLE* hWakeBear, HANDLE* noBeesPuttingHoney)
		: m_id(id)
		, m_pot(pot)
		, m_wakeBear(hWakeBear)
		, m_noBeesPuttingHoney(noBeesPuttingHoney)
		, m_gathered(false)
	{
		std::printf("Hello, I'm bee\n");
	}

	// ѕчЄлка собирает глоток мЄда и кладЄт его в горшок, пока не устанет
	void GatherAndStoreHoney()
	{
		while (true)
		{
			if (!m_gathered)
			{
				GatherHoneySip();
			}
			WaitForSingleObject(*m_noBeesPuttingHoney, INFINITE);
			if (m_pot.TryPutHoneySip())
			{
				std::printf("Bee #%u put gathered honey's sip into pot (%u/%u)\n", m_id, m_pot.GetHoneySipsCount(), m_pot.GetCapacity());
				m_gathered = false;
			}
			else
			{
				// в горшке больше нет места,
				//  нужно будить медвед€
				std::printf("Bee #%u is trying to put honey's sip but pot is full! Waking up bear...\n", m_id);
				SetEvent(*m_wakeBear);
			}
			ReleaseSemaphore(*m_noBeesPuttingHoney, 1u, NULL);
		}
	}

	void GatherHoneySip()
	{
		std::printf("Bee #%u gathering honey...\n", m_id);
		Sleep(300u);
		m_gathered = true;
		std::printf("Bee #%d gathered one honey's sip!\n", m_id);
	}

private:
	unsigned m_id;
	bool m_gathered;
	Pot& m_pot;
	HANDLE* m_wakeBear;
	HANDLE* m_noBeesPuttingHoney;
};
