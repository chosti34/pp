#include "stdafx.h"
#include "Random.h"

const unsigned ARGUMENTS_REQUIRED_COUNT = 2;
const std::string INVALID_ARGUMENTS_COUNT_MESSAGE =
	"Invalid arguments count!\n"
	"Usage: CalculatePiMonteCarloMethod.exe <iterations count>\n";
const float CIRCLE_RADIUS = 1.f;

bool IsPointInsideCircle(float x, float y, float radius)
{
	return (x * x) + (y * y) <= (radius * radius);
}

float CalculatePiMonteCarloMethod(unsigned iterations)
{
	unsigned pointsCount = 0;

	for (unsigned i = 0; i < iterations; ++i)
	{
		const float x = Random::Get(-CIRCLE_RADIUS, CIRCLE_RADIUS);
		const float y = Random::Get(-CIRCLE_RADIUS, CIRCLE_RADIUS);

		if (IsPointInsideCircle(x, y, CIRCLE_RADIUS))
		{
			++pointsCount;
		}
	}

	return 4.f * pointsCount / iterations;
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
