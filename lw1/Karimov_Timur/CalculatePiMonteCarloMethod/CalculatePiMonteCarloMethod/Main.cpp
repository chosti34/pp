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

void GetPointsCountRandomlyDistributedInsideCircle(unsigned iterations, unsigned& count)
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

	std::swap(count, pointsCount);
}

int main(int argc, char* argv[])
{
	if (argc != ARGUMENTS_REQUIRED_COUNT)
	{
		std::printf(INVALID_ARGUMENTS_COUNT_MESSAGE.c_str());
		return 1;
	}

	const unsigned iterations = 20000000u;
	unsigned threadsCount = 32;

	std::vector<std::thread> threads;
	std::vector<unsigned> results(threadsCount);

	for (int i = 0; i < threadsCount; ++i)
	{
		unsigned iterationsPerThread = iterations / threadsCount;
		if (i == threadsCount - 1)
		{
			iterationsPerThread += iterations % threadsCount;
		}
		threads.emplace_back(GetPointsCountRandomlyDistributedInsideCircle, iterationsPerThread, std::ref(results[i]));
	}

	for (auto& thread : threads)
	{
		if (thread.joinable())
		{
			thread.join();
		}
	}

	unsigned pointsInsideCircle = std::accumulate(results.begin(), results.end(), 0);
	std::cout << "Calculated PI: " << (4.f * float(pointsInsideCircle) / float(iterations)) << std::endl;
	return 0;
}
