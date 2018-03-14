#include "stdafx.h"
#include "Bear.h"

Bear::Bear(Pot& pot, HANDLE hWakeBearEvent, HANDLE hWakeBeesEvent)
	: m_pot(pot)
	, m_hWakeBearEvent(hWakeBearEvent)
	, m_hWakeBeesEvent(hWakeBeesEvent)
{
}

void Bear::EatHoney()
{
	while (true)
	{
		WaitForSingleObject(m_hWakeBearEvent, INFINITE);
		m_pot.PopHoneySip();
		std::printf("Nom-nom-nom! (Bear ate honey's sip)\n");
		if (m_pot.IsEmpty())
		{
			// ̸� � ������ ����������, ������ ������� ������ ����������,
			//  � ���� ������� �����...
			ResetEvent(m_hWakeBearEvent);
			SetEvent(m_hWakeBeesEvent);
		}
	}
}
