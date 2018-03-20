#include "stdafx.h"
#include "Bee.h"
#include "Random.h"

namespace
{
const unsigned HONEY_SIP_GATHERING_TIME_MS_MIN = 1500u;
const unsigned HONEY_SIP_GATHERING_TIME_MS_MAX = 5000u;
}

Bee::Bee(unsigned id, Pot& pot,
	std::shared_ptr<Event> wakeBearEvent,
	std::shared_ptr<Event> wakeBeesEvent,
	std::shared_ptr<Semaphore> beesPotAccessSemaphore)
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
		m_beesPotAccessSemaphore->WaitAndLock();
		m_wakeBeesEvent->WaitUntilSignalled();
		if (m_pot.TryPutHoneySip())
		{
			std::printf("Bee #%u put gathered honey's sip into pot (%u/%u)\n", m_id, m_pot.GetHoneySipsCount(), m_pot.GetCapacity());
			m_gathered = false;
		}
		else
		{
			std::printf("Bee #%u is trying to put honey's sip but pot is full! Waking up bear...\n", m_id);
			m_wakeBeesEvent->SetUnsignalled();
			m_wakeBearEvent->SetSignalled();
		}
		m_beesPotAccessSemaphore->Release();
	}
}

void Bee::GatherHoneySipIfNotGatheredYet()
{
	if (!m_gathered)
	{
		std::printf("Bee #%u gathering honey...\n", m_id);
		Sleep(Random::Get(HONEY_SIP_GATHERING_TIME_MS_MIN, HONEY_SIP_GATHERING_TIME_MS_MAX));
		m_gathered = true;
		std::printf("Bee #%d gathered one honey's sip!\n", m_id);
	}
}
