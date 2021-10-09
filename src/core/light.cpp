#include "apollo.h"
#include "light.h"

namespace apollo {

Light::Light(const Transform* lightToWorld, const Transform* worldToLight, const RGB& color, const float intensity) 
	: lightToWorld(lightToWorld), worldToLight(worldToLight), color(color), intensity(intensity) {}

}