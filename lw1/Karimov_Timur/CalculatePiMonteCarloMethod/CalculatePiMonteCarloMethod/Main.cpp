#include "stdafx.h"

namespace
{

class Randomizer
{
public:
	Randomizer()
		: m_randomDevice()
		, m_distribution()
		, m_engine(m_randomDevice())
	{
	}

	float GetRandomBetween(float min, float max)
	{
		std::uniform_real_distribution<float> m_distribution(min, max);
		return m_distribution(m_engine);
	}

private:
	std::random_device m_randomDevice;
	std::mt19937 m_engine;
	std::uniform_real_distribution<> m_distribution;
};

const unsigned ARGUMENTS_REQUIRED_COUNT = 2;
const std::string INVALID_ARGUMENTS_COUNT_MESSAGE =
	"Invalid arguments count!\n"
	"Usage: CalculatePiMonteCarloMethod.exe <iterations count>\n";

bool IsPointInsideCircle(float x, float y, float radius)
{
	return x * x + y * y <= radius * radius;
}

float CalculatePiMonteCarloMethod(unsigned iterations)
{
	Randomizer randomizer;
	unsigned pointsCount = 0;

	for (unsigned i = 0; i < iterations; ++i)
	{
		const float x = randomizer.GetRandomBetween(-1.f, 1.f);
		const float y = randomizer.GetRandomBetween(-1.f, 1.f);

		if (IsPointInsideCircle(x, y, 1))
		{
			++pointsCount;
		}
	}

	return 4.f * pointsCount / iterations;
}

}

int main(int argc, char* argv[])
{
	if (argc != ARGUMENTS_REQUIRED_COUNT)
	{
		std::printf(INVALID_ARGUMENTS_COUNT_MESSAGE.c_str());
		return 1;
	}
	std::cout << "Calculated PI: " << CalculatePiMonteCarloMethod(2000000u) << std::endl;
	return 0;
}
