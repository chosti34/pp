#pragma once
#include <chrono>

class Chronometer
{
public:
	using Seconds = std::chrono::duration<float>;

public:
	Chronometer();
	Seconds GrabDeltaTime();

private:
	std::chrono::time_point<std::chrono::steady_clock> m_lastTime;
};
