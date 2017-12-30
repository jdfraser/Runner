#pragma once

#include "Util/Common.h"

struct Bounds
{
	glm::vec3 min;
	glm::vec3 max;

	float getWidth() const { return max.x - min.x; }
	
	float getHeight() const { return max.y - min.y; }

	float getDepth() const { return max.z - min.z; }

	Bounds applyTransformation(glm::mat4 matrix) {
		Bounds result;

		glm::vec4 max(max.x, max.y, max.z, 1.0f);
		glm::vec4 min(min.x, min.y, min.z, 1.0f);

		result.max = matrix * max;
		result.min = matrix * min;

		return result;
	}
};
