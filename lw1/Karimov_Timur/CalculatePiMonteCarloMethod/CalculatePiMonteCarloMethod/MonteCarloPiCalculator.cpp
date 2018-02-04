#include "stdafx.h"
#include "MonteCarloPiCalculator.h"
#include "Random.h"
#include "ThreadManager.h"

namespace
{

struct CalculateThreadSharedInfo
{
	size_t iterations;
	size_t* pointsInside;
	size_t* currentIterations;
};

struct ProgressBarThreadSharedInfo
{
	size_t totalIterations;
	size_t* currentIterations;
};

bool IsPointInsideCircle(float x, float y, float radius)
{
	return (x * x) + (y * y) <= (radius * radius);
}

DWORD WINAPI CalculatePointsInsideCircle(LPVOID lParam)
{
	// is this thread-safe?
	static const float CIRCLE_RADIUS = 1.f;

	CalculateThreadSharedInfo* info = reinterpret_cast<CalculateThreadSharedInfo*>(lParam);
	for (size_t i = 0; i < info->iterations; ++i)
	{
		const float x = Random::Get(-CIRCLE_RADIUS, CIRCLE_RADIUS);
		const float y = Random::Get(-CIRCLE_RADIUS, CIRCLE_RADIUS);
		if (IsPointInsideCircle(x, y, CIRCLE_RADIUS))
		{
			// using this function because we don't want to create mutex just for incrementing value
			// according to: https://weseetips.wordpress.com/tag/interlockedincrement/
			InterlockedIncrement(info->pointsInside);
		}
		InterlockedIncrement(info->currentIterations);
	}
	return 0;
}

DWORD WINAPI PrintCalculationProgress(LPVOID lParam)
{
	ProgressBarThreadSharedInfo* info = reinterpret_cast<ProgressBarThreadSharedInfo*>(lParam);
	do
	{
		std::cout << "[" << *info->currentIterations << "/" << info->totalIterations << "]\r";
		std::this_thread::sleep_for(std::chrono::duration<float>(0.05f));
	}
	while (*info->currentIterations != info->totalIterations);
	std::cout << "[" << *info->currentIterations << "/" << info->totalIterations << "]" << std::endl;
	return 0;
}

size_t GetPointsCountInsideCircle(size_t totalIterations, size_t threadsCount)
{
	if (totalIterations == 0 || threadsCount == 0)
	{
		throw std::invalid_argument("can't calculate PI with such parameters");
	}

	ThreadManager threads;
	std::vector<CalculateThreadSharedInfo> threadSharedInfos;

	size_t currentIterations = 0;
	size_t pointsInsideCircle = 0;

	for (size_t i = 0; i < threadsCount; ++i)
	{
		threadSharedInfos.push_back({ totalIterations / threadsCount, &pointsInsideCircle, &currentIterations });
	}
	threadSharedInfos.back().iterations += totalIterations % threadsCount;

	for (size_t i = 0; i < threadsCount; ++i)
	{
		threads.Add(CalculatePointsInsideCircle, &threadSharedInfos[i]);
	}

	ProgressBarThreadSharedInfo progressInfo = { totalIterations, &currentIterations };
	threads.Add(PrintCalculationProgress, &progressInfo);

	threads.JoinAll();
	return pointsInsideCircle;
}

}

float MonteCarloPiCalculator::Calculate(size_t totalIterations, size_t threadsCount)
{
	return 4.f * float(GetPointsCountInsideCircle(totalIterations, threadsCount)) / float(totalIterations);
}
