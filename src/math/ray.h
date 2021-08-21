#ifndef APOLLO_MATH_RAY_H
#define APOLLO_MATH_RAY_H

#include "apollo.h"
#include "point3.h"
#include "vector3.h"

namespace apollo {

class Ray {
	public:
		Ray(); 
		Ray(const Point3f& o, const Vector3f& d, float tMax = Infinity, float time = 0.f);

		// Find point at t
		Point3f operator()(float t) const; 

		// Ray public data
		Point3f o;
		Vector3f d;
		mutable float tMax;
		float time;
};

// Print ray
std::ostream& operator<<(std::ostream& out, const Ray& r);

}

#endif
