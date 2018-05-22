#include "stdafx.h"
#include "Random.h"
#include <climits>

Random::Random()
	: m_engine(std::random_device{}())
{
}

float Random::Get(float min, float max)
{
	std::uniform_real_distribution<float> distribution(min, std::nextafter(max, FLT_EPSILON));
	return distribution(m_engine);
}
