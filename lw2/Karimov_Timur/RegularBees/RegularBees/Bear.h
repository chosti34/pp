#pragma once
#include <cstdio>
#include "Pot.h"
#include <Windows.h>
#include <cassert>
#include "Chronometer.h"

class Bear
{
public:
	Bear(Pot& pot, HANDLE hWakeBearEvent, HANDLE hBeesPotAccessSemaphore);
	void EatHoney();

private:
	Pot& m_pot;
	HANDLE m_hWakeBearEvent;
	HANDLE m_hWakeBeesEvent;
};
