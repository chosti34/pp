#pragma once
#include <cstdio>
#include "Pot.h"
#include <Windows.h>
#include "Chronometer.h"

class Bee
{
public:
	Bee(unsigned id, Pot& pot, HANDLE hWakeBearEvent, HANDLE hWakeBeesEvent, HANDLE hBeesPotAccessSemaphore);

	void GatherAndStoreHoney();

private:
	void GatherHoneySip();

	unsigned m_id;
	bool m_gathered;
	Pot& m_pot;
	HANDLE m_hWakeBearEvent;
	HANDLE m_hWakeBeesEvent;
	HANDLE m_hBeesPotAccessSemaphore;
};
