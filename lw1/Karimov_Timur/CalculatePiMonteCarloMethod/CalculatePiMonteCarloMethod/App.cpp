#include "stdafx.h"
#include "App.h"
#include "Random.h"

namespace
{
	struct ThreadSharedInfo
	{
		size_t iterations;
		size_t pointsInside;
	};

	const float CIRCLE_RADIUS = 1.f;

	bool IsPointInsideCircle(float x, float y, float radius)
	{
		return (x * x) + (y * y) <= (radius * radius);
	}

	DWORD WINAPI CalculatePointsInsideCircle(LPVOID lParam)
	{
		ThreadSharedInfo* info = reinterpret_cast<ThreadSharedInfo*>(lParam);
		for (size_t i = 0; i < info->iterations; ++i)
		{
			const float x = Random::Get(-CIRCLE_RADIUS, CIRCLE_RADIUS);
			const float y = Random::Get(-CIRCLE_RADIUS, CIRCLE_RADIUS);

			if (IsPointInsideCircle(x, y, CIRCLE_RADIUS))
			{
				++info->pointsInside;
			}
		}
		return 0;
	}
}

App::App()
	: m_hThreads()
{
}

App::~App()
{
	for (auto& hThread : m_hThreads)
	{
		CloseHandle(hThread);
	}
}

float App::Execute(size_t iterations, size_t threads)
{
	if (iterations == 0 || threads == 0)
	{
		throw std::invalid_argument("can't calculate PI with such parameters");
	}

	std::vector<ThreadSharedInfo> results;
	for (size_t i = 0; i < threads; ++i)
	{
		results.push_back({ iterations / threads, 0 });
	}
	results.back().iterations += iterations % threads;

	for (size_t i = 0; i < threads; ++i)
	{
		m_hThreads.push_back(CreateThread(NULL, 0, CalculatePointsInsideCircle, &results[i], 0, 0));
	}

	WaitForMultipleObjects(DWORD(threads), m_hThreads.data(), TRUE, INFINITE);

	size_t pointsCount = 0;
	std::for_each(results.begin(), results.end(), [&pointsCount](const ThreadSharedInfo& info) {
		pointsCount += info.pointsInside;
	});

	return 4.f * float(pointsCount) / float(iterations);
}
