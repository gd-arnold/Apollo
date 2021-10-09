#ifndef APOLLO_CORE_LIGHT_H
#define APOLLO_CORE_LIGHT_H

#include "apollo.h"
#include "transform.h"
#include "rgb.h"

namespace apollo {

class Light {
public:
	Light(const Transform* lightToWorld, const Transform* worldToLight, const RGB& color, const float intensity);

public:
	const Transform *lightToWorld, *worldToLight;
	const RGB& color;
	const float intensity;
};

}

#endif
