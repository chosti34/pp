#pragma once
#include <Windows.h>

// Structures and functions for multi-thread data handling
// TODO: shared_ptr may be better solution
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

DWORD WINAPI DumpCurrentProgressToStdout(LPVOID lParam);
DWORD WINAPI CountPointsInsideCircle(LPVOID lParam);

// Interface for strategy
class IMonteCarloCalculatePiStrategy
{
public:
	virtual float Calculate() = 0;
};
