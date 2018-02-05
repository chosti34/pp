#include "stdafx.h"
#include "SingleThreadedCalculatePiStrategy.h"
#include "Random.h"
#include "Math.h"
#include "ThreadManager.h"

SingleThreadedCalculatePiStrategy::SingleThreadedCalculatePiStrategy(size_t iterationsCount)
	: m_iterationsCount(iterationsCount)
{
}

float SingleThreadedCalculatePiStrategy::Calculate()
{
	size_t points = 0;
	size_t currentIterations = 0;

	CalculateThreadSharedInfo calculateInfo = { m_iterationsCount, &points, &currentIterations };
	ProgressBarThreadSharedInfo progressInfo = { m_iterationsCount, &currentIterations };

	// All calculations will be performed in the same thread, but progress bar
	// will work in another thread to prevent slowing calculations time
	ThreadManager threadManager;
	threadManager.Add(DumpCurrentProgressToStdout, &progressInfo);

	CountPointsInsideCircle(&calculateInfo);

	threadManager.JoinAll();
	return 4.f * float(points) / float(m_iterationsCount);
}
