#pragma once
#include "Pot.h"
#include "Event.h"
#include "Semaphore.h"
#include <memory>

class Bee
{
public:
	Bee(unsigned id, Pot& pot,
		std::shared_ptr<Event> wakeBearEvent,
		std::shared_ptr<Event> wakeBeesEvent,
		std::shared_ptr<Semaphore> beesPotAccessSemaphore);

	void GatherAndStoreHoney();

private:
	void GatherHoneySipIfNotGatheredYet();

	Pot& m_pot;

	std::shared_ptr<Event> m_wakeBearEvent;
	std::shared_ptr<Event> m_wakeBeesEvent;
	std::shared_ptr<Semaphore> m_beesPotAccessSemaphore;

	unsigned m_id;
	bool m_gathered;
};
