#pragma once
#include "Pot.h"
#include "ForwardDeclarations.h"

class Bear
{
public:
	Bear(Pot& pot, HANDLE wakeBearEvent, HANDLE wakeBeesEvent);
	void EatHoney();

private:
	Pot& m_pot;
	HANDLE m_wakeBearEvent;
	HANDLE m_wakeBeesEvent;
};
