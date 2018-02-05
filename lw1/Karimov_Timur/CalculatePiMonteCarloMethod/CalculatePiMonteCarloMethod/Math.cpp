#include "stdafx.h"
#include "Math.h"

bool Math::CircleHitTest(float x, float y, float radius)
{
	return (x * x) + (y * y) <= (radius * radius);
}
