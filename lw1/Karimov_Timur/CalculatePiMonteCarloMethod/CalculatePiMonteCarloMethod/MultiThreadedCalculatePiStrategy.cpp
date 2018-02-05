#include "stdafx.h"
#include "MultiThreadedCalculatePiStrategy.h"
#include "ThreadManager.h"
#include "Random.h"
#include "Math.h"
#include "MonteCarloPiCalculator.h"

namespace
{
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
		threads.Add(CountPointsInsideCircle, &threadSharedInfos[i]);
	}

	ProgressBarThreadSharedInfo progressInfo = { totalIterations, &currentIterations };
	threads.Add(DumpCurrentProgressToStdout, &progressInfo);

	threads.JoinAll();
	return pointsInsideCircle;
}
}

MultiThreadedCalculatePiStrategy::MultiThreadedCalculatePiStrategy(size_t iterationsCount, size_t threadsCount)
	: m_iterationsCount(iterationsCount)
	, m_threadsCount(threadsCount)
{
}

float MultiThreadedCalculatePiStrategy::Calculate()
{
	return 4.f * float(GetPointsCountInsideCircle(m_iterationsCount, m_threadsCount)) / m_iterationsCount;
}
