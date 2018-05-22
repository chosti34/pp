#include "stdafx.h"
#include "PiCalculator.h"
#include "Random.h"
#include <omp.h>

namespace
{
// Подразумевается, что центр окружности имеет координаты (0, 0)
bool CircleHitTest(float x, float y, float radius)
{
	return std::pow(x, 2) + std::pow(y, 2) <= std::pow(radius, 2);
}
}

float PiCalculator::Calculate(int iterations)
{
	int inside = 0;

	#pragma omp parallel
	{
		Random random;
		#pragma omp for
		for (int i = 0; i < iterations; ++i)
		{
			const float x = random.Get(-1.f, 1.f);
			const float y = random.Get(-1.f, 1.f);
			if (CircleHitTest(x, y, 1.f))
			{
				#pragma omp atomic
				++inside;
			}
		}
	}

	return 4.f * float(inside) / float(iterations);
}
