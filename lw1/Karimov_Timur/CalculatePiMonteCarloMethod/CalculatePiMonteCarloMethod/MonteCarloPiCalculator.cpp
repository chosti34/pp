#include "stdafx.h"
#include "MonteCarloPiCalculator.h"
#include "Random.h"
#include "ThreadManager.h"
#include "MultiThreadedCalculatePiStrategy.h"
#include "SingleThreadedCalculatePiStrategy.h"

namespace
{
std::unique_ptr<IMonteCarloCalculatePiStrategy> GetStrategy(size_t totalIterations, size_t threadsCount)
{
	if (threadsCount == 1)
	{
		return std::make_unique<SingleThreadedCalculatePiStrategy>(totalIterations);
	}
	return std::make_unique<MultiThreadedCalculatePiStrategy>(totalIterations, threadsCount);
}
}

float MonteCarloPiCalculator::Calculate(size_t totalIterations, size_t threadsCount)
{
	auto strategy = GetStrategy(totalIterations, threadsCount);
	return strategy->Calculate();
}
