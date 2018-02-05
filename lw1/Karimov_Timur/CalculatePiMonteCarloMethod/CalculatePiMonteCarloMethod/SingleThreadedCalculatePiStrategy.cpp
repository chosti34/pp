#include "stdafx.h"
#include "SingleThreadedCalculatePiStrategy.h"
#include "Random.h"
#include "Math.h"
#include "ThreadManager.h"

namespace
{
struct ProgressBarThreadSharedInfo
{
	size_t totalIterations;
	size_t* currentIterations;
};

DWORD WINAPI DumpCurrentProgressToStdout(LPVOID lParam)
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

size_t CountPointsInsideCircle(size_t iterationsCount)
{
	static const float radius = 1.f;
	size_t count = 0;
	size_t progress = 0;

	ThreadManager threadManager;
	ProgressBarThreadSharedInfo progressBarInfo = { iterationsCount, &progress };

	threadManager.Add(DumpCurrentProgressToStdout, &progressBarInfo);

	for (size_t i = 0; i < iterationsCount; ++i)
	{
		const float x = Random::Get(-radius, radius);
		const float y = Random::Get(-radius, radius);
		if (Math::CircleHitTest(x, y, radius))
		{
			InterlockedIncrement(&count);
		}
		InterlockedIncrement(&progress);
	}

	threadManager.JoinAll();
	return count;
}
}

SingleThreadedCalculatePiStrategy::SingleThreadedCalculatePiStrategy(size_t iterationsCount)
	: m_iterationsCount(iterationsCount)
{
}

float SingleThreadedCalculatePiStrategy::Calculate()
{
	return 4.f * float(CountPointsInsideCircle(m_iterationsCount)) / float(m_iterationsCount);
}
