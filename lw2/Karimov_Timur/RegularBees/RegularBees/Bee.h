#pragma once
#include "Pot.h"
#include "ForwardDeclarations.h"

class Bee
{
public:
	Bee(unsigned id, Pot& pot,
		HANDLE wakeBearEvent,
		HANDLE wakeBeesEvent,
		HANDLE beesPotAccessSemaphore);

	void GatherAndStoreHoney();

private:
	void GatherHoneySipIfNotGatheredYet();

	Pot& m_pot;

	HANDLE m_wakeBearEvent;
	HANDLE m_wakeBeesEvent;
	HANDLE m_beesPotAccessSemaphore;

	unsigned m_id;
	bool m_gathered;
};
