#pragma once
#include "IMonteCarloCalculatePiStrategy.h"

class SingleThreadedCalculatePiStrategy : public IMonteCarloCalculatePiStrategy
{
public:
	SingleThreadedCalculatePiStrategy(size_t iterationsCount);
	float Calculate() override;

private:
	size_t m_iterationsCount;
};
