#include "stdafx.h"
#include "Bear.h"

Bear::Bear(Pot& pot, HANDLE wakeBearEvent, HANDLE wakeBeesEvent)
	: m_pot(pot)
	, m_wakeBearEvent(wakeBearEvent)
	, m_wakeBeesEvent(wakeBeesEvent)
{
}

void Bear::EatHoney()
{
	while (true)
	{
		WaitForSingleObject(m_wakeBearEvent, INFINITE);
		m_pot.PopHoneySip();
		std::printf("Nom-nom-nom! (Bear ate honey's sip)\n");
		if (m_pot.IsEmpty())
		{
			// Мёд в горшке закончился, значит говорим пчёлам проснуться,
			//  а сами ложимся спать...
			ResetEvent(m_wakeBearEvent);
			SetEvent(m_wakeBeesEvent);
		}
	}
}
