#include "stdafx.h"
#include "Bee.h"

Bee::Bee(unsigned id, Pot& pot,
	HANDLE wakeBearEvent,
	HANDLE wakeBeesEvent,
	HANDLE beesPotAccessSemaphore)
	: m_id(id)
	, m_pot(pot)
	, m_wakeBearEvent(wakeBearEvent)
	, m_wakeBeesEvent(wakeBeesEvent)
	, m_beesPotAccessSemaphore(beesPotAccessSemaphore)
	, m_gathered(false)
{
}

void Bee::GatherAndStoreHoney()
{
	while (true)
	{
		GatherHoneySipIfNotGatheredYet();
		WaitForSingleObject(m_wakeBeesEvent, INFINITE);
		WaitForSingleObject(m_beesPotAccessSemaphore, INFINITE);
		if (m_pot.TryPutHoneySip())
		{
			std::printf("Bee #%u put gathered honey's sip into pot (%u/%u)\n", m_id, m_pot.GetHoneySipsCount(), m_pot.GetCapacity());
			m_gathered = false;
		}
		else
		{
			std::printf("Bee #%u is trying to put honey's sip but pot is full! Waking up bear...\n", m_id);
			ResetEvent(m_wakeBeesEvent);
			SetEvent(m_wakeBearEvent);
		}
		ReleaseSemaphore(m_beesPotAccessSemaphore, 1u, NULL);
	}
}

void Bee::GatherHoneySipIfNotGatheredYet()
{
	if (!m_gathered)
	{
		std::printf("Bee #%u gathering honey...\n", m_id);
		Sleep(300u);
		m_gathered = true;
		std::printf("Bee #%d gathered one honey's sip!\n", m_id);
	}
}
