#pragma once

#include "Util/Common.h"

struct Bounds
{
	glm::vec3 min;
	glm::vec3 max;

	float getWidth() { return max.x - min.x; }
	
	float getHeight() { return max.y - min.y; }

	float getDepth() { return max.z - min.z; }
};
