#include "stdafx.h"
#include "Random.h"

int Random::Get(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(GetEngineInstance());
}

float Random::Get(float min, float max)
{
	std::uniform_real_distribution<float> distribution(min,
		std::nextafter(max, std::numeric_limits<float>::max()));
	return distribution(GetEngineInstance());
}

double Random::Get(double min, double max)
{
	std::uniform_real_distribution<double> distribution(min,
		std::nextafter(max, std::numeric_limits<double>::max()));
	return distribution(GetEngineInstance());
}

// TODO: is this thread-safe?
std::mt19937& Random::GetEngineInstance()
{
	static std::random_device device; // seeder
	static std::mt19937 engine(device()); // engine
	return engine;
}
