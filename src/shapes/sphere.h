#ifndef APOLLO_SHAPE_SPHERE_H
#define APOLLO_SHAPE_SPHERE_H

#include "apollo.h"
#include "shape.h"

namespace apollo {

// Sphere origin is always defined at the center of the coordinate system in object space
class Sphere : public Shape {
	public:
		Sphere(const Transform* objectToWorld, const Transform* worldToObject, bool reverseOrientation, float radius); 
			
		// Check if a sphere is intersected by a ray
		bool Intersect(const Ray& ray) const override;

		// Sphere bounding box in object coordinates
		Bounds3f ObjectBound() const override;
		// Sphere bounding box in world coordinates
		Bounds3f WorldBound() const override;

		// Sphere surface area
		float Area() const override;
	private:
		const float radius;

};	

}

#endif
