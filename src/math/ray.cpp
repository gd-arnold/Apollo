#include "apollo.h"
#include "ray.h"

namespace apollo {

Ray::Ray() : tMax(Infinity), time(0.f) {}

Ray::Ray(const Point3f& o, const Vector3f& d, float tMax, float time) : o(o), d(d), tMax(tMax), time(time) {}

// Find point at t
Point3f Ray::operator()(float t) const {
	return o + t*d;
}

// Print ray
std::ostream& operator<<(std::ostream& out, const Ray& r) {
	return out << "[o=" << r.o << ", d=" << r.d << ", tMax=" << r.tMax << ", time=" << r.time << "]";
}

}
