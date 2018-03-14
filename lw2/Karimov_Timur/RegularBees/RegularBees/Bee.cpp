#include "stdafx.h"
#include "Bee.h"

Bee::Bee(unsigned id, Pot& pot, HANDLE hWakeBearEvent, HANDLE hWakeBeesEvent, HANDLE hBeesPotAccessSemaphore)
	: m_id(id)
	, m_pot(pot)
	, m_hWakeBearEvent(hWakeBearEvent)
	, m_hWakeBeesEvent(hWakeBeesEvent)
	, m_hBeesPotAccessSemaphore(hBeesPotAccessSemaphore)
	, m_gathered(false)
{
}

void Bee::GatherAndStoreHoney()
{
	while (true)
	{
		GatherHoneySip();
		WaitForSingleObject(m_hWakeBeesEvent, INFINITE);
		WaitForSingleObject(m_hBeesPotAccessSemaphore, INFINITE);
		if (m_pot.TryPutHoneySip())
		{
			std::printf("Bee #%u put gathered honey's sip into pot (%u/%u)\n", m_id, m_pot.GetHoneySipsCount(), m_pot.GetCapacity());
			m_gathered = false;
		}
		else
		{
			std::printf("Bee #%u is trying to put honey's sip but pot is full! Waking up bear...\n", m_id);
			ResetEvent(m_hWakeBeesEvent);
			SetEvent(m_hWakeBearEvent);
		}
		ReleaseSemaphore(m_hBeesPotAccessSemaphore, 1u, NULL);
	}
}

void Bee::GatherHoneySip()
{
	if (!m_gathered)
	{
		std::printf("Bee #%u gathering honey...\n", m_id);
		Sleep(300u);
		m_gathered = true;
		std::printf("Bee #%d gathered one honey's sip!\n", m_id);
	}
}
