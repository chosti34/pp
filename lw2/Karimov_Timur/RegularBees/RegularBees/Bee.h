#pragma once
#include <cstdio>
#include "Pot.h"
#include <Windows.h>

class Bee
{
public:
	Bee(Pot& pot, HANDLE* hWakeBear)
		: m_pot(pot)
		, m_wakeBear(hWakeBear)
	{
		std::printf("Hello, I'm bee\n");
	}

	// ������ �������� ������ ��� � ����� ��� � ������, ���� �� �������
	void GatherAndStoreHoney()
	{
		while (true)
		{
			Sleep(300);
			if (m_pot.TryPutHoneySip())
			{
				std::printf("Bee gathered one honey sip\n");
			}
			else
			{
				// � ������ ������ ��� �����,
				//  ����� ������ �������
				std::printf("Pot is full! Waking up bear...\n");
				SetEvent(*m_wakeBear);
			}
		}
	}

private:
	Pot& m_pot;
	HANDLE* m_wakeBear;
};
