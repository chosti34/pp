#include "stdafx.h"
#include "Random.h"

int Random::Get(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(GetEngineInstance());
}

std::mt19937 & Random::GetEngineInstance()
{
	static std::random_device device;
	static std::mt19937 engine(device());
	return engine;
}
