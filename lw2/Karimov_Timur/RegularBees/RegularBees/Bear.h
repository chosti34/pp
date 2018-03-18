#pragma once
#include "Pot.h"
#include "Event.h"
#include <memory>

class Bear
{
public:
	Bear(Pot& pot, std::shared_ptr<Event> wakeBearEvent, std::shared_ptr<Event> wakeBeesEvent);
	void EatHoney();

private:
	Pot& m_pot;

	// maybe use just a reference
	std::shared_ptr<Event> m_wakeBearEvent;
	std::shared_ptr<Event> m_wakeBeesEvent;
};
