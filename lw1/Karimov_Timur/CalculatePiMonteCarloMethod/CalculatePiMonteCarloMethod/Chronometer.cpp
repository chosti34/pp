#include "stdafx.h"
#include "Chronometer.h"

Chronometer::Chronometer()
	: m_lastTime(std::chrono::steady_clock::now())
{
}

Chronometer::Seconds Chronometer::GrabDeltaTime()
{
	auto nowTime = std::chrono::steady_clock::now();
	auto timePassed = nowTime - m_lastTime;
	m_lastTime = nowTime;
	return std::chrono::duration_cast<Seconds>(timePassed);
}
