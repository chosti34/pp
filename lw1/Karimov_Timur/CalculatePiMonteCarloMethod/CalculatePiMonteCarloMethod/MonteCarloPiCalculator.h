#pragma once
#include <Windows.h>

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
DWORD WINAPI CountPointsInsideCircleInChildThread(LPVOID lParam);

class MonteCarloPiCalculator
{
public:
	static float Calculate(size_t totalIterations, size_t threadsCount);
};
