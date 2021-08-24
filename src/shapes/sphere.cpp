#include "apollo.h"
#include "sphere.h"
#include "vector3.h"
#include "point3.h"

namespace apollo {
	Sphere::Sphere(const Transform* objectToWorld, const Transform* worldToObject, 
			bool reverseOrientation, float radius)
		: Shape(objectToWorld, worldToObject, reverseOrientation), radius(radius) {}
	
	bool Sphere::Intersect(const Ray& ray) const {
		// Transform ray to object space
		Ray r = (*worldToObject)(ray);
		
		// Compute quadratic coefficients
		float a = r.d.x * r.d.x + r.d.y * r.d.y + r.d.z * r.d.z;
		float b = 2.0f * (r.d.x * r.o.x + r.d.y * r.o.y + r.d.z * r.o.z);
		float c = r.o.x * r.o.x + r.o.y * r.o.y + r.o.z * r.o.z - radius * radius;

		// Solve quadratic equation
		float t0, t1;
		if (!Quadratic(a, b, c, t0, t1))
			return false;
		
		// Ensure solutions pass ray constraints	
		if (t0 > r.tMax && t1 > r.tMax || t0 < 0.0f && t1 < 0.0f)
			return false;

		return true;
	}

	Bounds3f Sphere::ObjectBound() const {
		return Bounds3f(Point3f(-radius), Point3f(radius));
	}
	
	Bounds3f Sphere::WorldBound() const {
		Point3f center = (*objectToWorld)(Point3f(0.0f));
		return Bounds3f(center - radius, center + radius);
	}

	float Sphere::Area() const {
		return 4 * PI * radius * radius;
	}

} 
