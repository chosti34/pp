#include "stdafx.h"
#include "Bear.h"

namespace
{
const unsigned EATING_HONEY_SIP_TIME_MS = 500u;
}

Bear::Bear(Pot& pot, std::shared_ptr<Event> wakeBearEvent, std::shared_ptr<Event> wakeBeesEvent)
	: m_pot(pot)
	, m_wakeBearEvent(wakeBearEvent)
	, m_wakeBeesEvent(wakeBeesEvent)
{
}

void Bear::EatHoney()
{
	while (true)
	{
		m_wakeBearEvent->WaitUntilSignalled();
		m_pot.PopHoneySip();
		std::printf("Nom-nom-nom! (Bear ate honey's sip)\n");
		Sleep(EATING_HONEY_SIP_TIME_MS);
		if (m_pot.IsEmpty())
		{
			// Мёд в горшке закончился, значит говорим пчёлам проснуться,
			//  а сами ложимся спать...
			m_wakeBearEvent->SetUnsignalled();
			m_wakeBeesEvent->SetSignalled();
		}
	}
}
