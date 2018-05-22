#pragma once
#include <random>

class Random
{
public:
	Random();
	float Get(float min, float max);

private:
	std::mt19937 m_engine;
};
