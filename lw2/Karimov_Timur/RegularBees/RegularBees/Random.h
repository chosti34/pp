#pragma once
#include <random>

class Random
{
public:
	static int Get(int min, int max);

private:
	static std::mt19937& GetEngineInstance();
};
