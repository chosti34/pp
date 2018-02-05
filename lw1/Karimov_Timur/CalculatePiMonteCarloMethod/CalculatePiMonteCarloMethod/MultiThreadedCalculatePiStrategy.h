#pragma once
#include "IMonteCarloCalculatePiStrategy.h"

class MultiThreadedCalculatePiStrategy : public IMonteCarloCalculatePiStrategy
{
public:
	MultiThreadedCalculatePiStrategy(size_t iterationsCount, size_t threadsCount);
	float Calculate() override;

private:
	size_t m_threadsCount;
	size_t m_iterationsCount;
};
