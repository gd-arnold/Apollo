#ifndef APOLLO_SHAPE_SHAPE_H
#define APOLLO_SHAPE_SHAPE_H

#include "apollo.h"
#include "transform.h"
#include "ray.h"
#include "bounds3.h"
#include "interaction.h"

namespace apollo {
// General shape interface
class Shape {
	public:
		Shape(const Transform* objectToWorld, const Transform* worldToObject, bool reverseOrientation);
		
		virtual ~Shape() {};

		// Check if a shape is intersected by a ray
		// TODO Create a SurfaceInteraction entity which stores information about the intersected point 
		virtual bool Intersect(const Ray& ray, SurfaceInteraction* surf = nullptr) const = 0;

		// Shape bounding box in object coordinates
		virtual Bounds3f ObjectBound() const = 0;
		// Shape bounding box in world coordinates
		virtual Bounds3f WorldBound() const = 0;

		// Compute surface area of a shape
		virtual float Area() const = 0;

	public:
		// Transform of the shape from object to world space and vice versa
		const Transform *objectToWorld, *worldToObject;
		// Indicates whether shape's surface normal direction must be reversed from the default
		const bool reverseOrientation;
		// Indicates whether object to world transformation changes coordinate system handedness
		const bool transformChangesHandedness;
}; 

}

#endif
