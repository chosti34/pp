#include "stdafx.h"
#include "MultiThreadedCalculatePiStrategy.h"
#include "ThreadManager.h"
#include "Random.h"
#include "Math.h"

namespace
{
size_t CountPointsMultithreaded(size_t iterationsCount, size_t threadsCount)
{
	if (iterationsCount == 0 || threadsCount == 0)
	{
		throw std::invalid_argument("can't calculate PI with such parameters");
	}

	size_t currentIterations = 0;
	size_t count = 0;

	std::vector<CalculateThreadSharedInfo> threadSharedInfos;
	for (size_t i = 0; i < threadsCount; ++i)
	{
		threadSharedInfos.push_back({ iterationsCount / threadsCount, &count, &currentIterations });
	}

	// If iterations count cannot be whole divided by threads count, last thread will process all remaining iterations
	threadSharedInfos.back().iterations += iterationsCount % threadsCount;

	ThreadManager threads;
	for (size_t i = 0; i < threadsCount; ++i)
	{
		threads.Add(CountPointsInsideCircle, &threadSharedInfos[i]);
	}

	// Printing progress bar will be handled in another thread
	ProgressBarThreadSharedInfo progressInfo = { iterationsCount, &currentIterations };
	threads.Add(DumpCurrentProgressToStdout, &progressInfo);

	threads.JoinAll();
	return count;
}
}

MultiThreadedCalculatePiStrategy::MultiThreadedCalculatePiStrategy(size_t iterationsCount, size_t threadsCount)
	: m_iterationsCount(iterationsCount)
	, m_threadsCount(threadsCount)
{
}

float MultiThreadedCalculatePiStrategy::Calculate()
{
	return 4.f * float(CountPointsMultithreaded(m_iterationsCount, m_threadsCount)) / m_iterationsCount;
}
