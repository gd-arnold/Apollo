#ifndef APOLLO_MATH_RAY_H
#define APOLLO_MATH_RAY_H

#include "apollo.h"
#include "point3.h"
#include "vector3.h"

namespace apollo {

class Ray {
	public:
		Ray() : tMax(Infinity), time(0.f) {}
		Ray(const Point3f& o, const Vector3f& d, float tMax = Infinity, float time = 0.f)
		: o(o), d(d), tMax(tMax), time(time) {}

		// Find point at t
		Point3f operator()(float t) const { 
			return o + t * d;
		}

		// Ray public data
		Point3f o;
		Vector3f d;
		mutable float tMax;
		float time;
};

// Print
inline std::ostream& operator<<(std::ostream& out, const Ray& r) {
	return out << "[o=" << r.o << ", d=" << r.d << ", tMax=" << r.tMax << ", time=" << r.time << "]\n";
}

}

#endif
