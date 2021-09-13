#ifndef APOLLO_SHAPES_TRIANGLE_H
#define APOLLO_SHAPES_TRIANGLE_H

#include "apollo.h"
#include "shape.h"
#include "point3.h"

namespace apollo {

class Triangle : public Shape 
{
public:
	// NOTE: Verticies must be specified in clockwise order (from the point of view of the camera) 
	// if the triangle needs to be front-facing
	Triangle(const Transform* objectToWorld, const Transform* worldToObject, bool reverseOrientation,
		const Point3f v0, const Point3f v1, const Point3f v2);

	// Check if a triangle is intersected by a ray
	// Apollo implements the Möller–Trumbore ray-triangle intersection algorithm
	bool Intersect(const Ray& ray, SurfaceInteraction* surf = nullptr) const override;

	// Triangle bounding box in object coordinates
	Bounds3f ObjectBound() const override;
	// Triangle bounding box in world coordinates
	Bounds3f WorldBound() const override;

	// Triangle surface area
	float Area() const override;
private:
	Point3f v0, v1, v2;
};

}

#endif