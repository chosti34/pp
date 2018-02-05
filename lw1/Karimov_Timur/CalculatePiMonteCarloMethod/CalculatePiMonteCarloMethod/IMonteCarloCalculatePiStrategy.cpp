#include "stdafx.h"
#include "IMonteCarloCalculatePiStrategy.h"
#include "Random.h"
#include "Math.h"

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

DWORD CountPointsInsideCircle(LPVOID lParam)
{
	// Is this thread-safe?
	static const float radius = 1.f;

	CalculateThreadSharedInfo* info = reinterpret_cast<CalculateThreadSharedInfo*>(lParam);
	for (size_t i = 0; i < info->iterations; ++i)
	{
		const float x = Random::Get(-radius, radius);
		const float y = Random::Get(-radius, radius);
		if (Math::CircleHitTest(x, y, radius))
		{
			// Using this function because we don't want to create mutex just for incrementing value
			// according to: https://weseetips.wordpress.com/tag/interlockedincrement/
			InterlockedIncrement(info->pointsInside);
		}
		InterlockedIncrement(info->currentIterations);
	}
	return 0;
}
