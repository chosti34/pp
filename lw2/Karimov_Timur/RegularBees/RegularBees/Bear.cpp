#include "stdafx.h"
#include "Bear.h"

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
		if (m_pot.IsEmpty())
		{
			// ̸� � ������ ����������, ������ ������� ������ ����������,
			//  � ���� ������� �����...
			m_wakeBearEvent->SetUnsignalled();
			m_wakeBeesEvent->SetSignalled();
		}
	}
}
