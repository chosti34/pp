#pragma once
#include <random>

class Random
{
public:
	static int Get(int min, int max);
	static float Get(float min, float max);
	static double Get(double min, double max);

private:
	static std::mt19937& GetEngineInstance();
};
