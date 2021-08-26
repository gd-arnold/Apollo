#ifndef APOLLO_MATH_INTERACTION_H
#define APOLLO_MATH_INTERACTION_H

#include "point3.h"
#include "normal3.h"
#include "vector3.h"

namespace apollo {

class Interaction {
	public:
		Interaction(const Point3f &p, const Normal3f &n, const Vector3f &wo, float time);
	protected:
		// Intersected point
		Point3f p;
		// Time of intersection
		float time;
		// Negative ray direction
		Vector3f wo;
		// Surface normal
		Normal3f n;
		
};

}

#endif
