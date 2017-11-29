#pragma once

#include "Util/Common.h"

struct Bounds
{
	glm::vec3 min;
	glm::vec3 max;

	float getWidth() const { return max.x - min.x; }
	
	float getHeight() const { return max.y - min.y; }

	float getDepth() const { return max.z - min.z; }
};
