#ifndef APOLLO_CORE_PRIMITIVE_H
#define APOLLO_CORE_PRIMITIVE_H

#include "apollo.h"
#include "bounds3.h"
#include "ray.h"
#include "interaction.h"
#include "shape.h"

namespace apollo {

// A primitive is a spatial data structure. Many different shapes and materials can be attached to it
class Primitive {
	public:
		Primitive(const Shape* shape);

		// Get the axis aligned bounding box of the primitive in world space
		Bounds3f WorldBound();
		
		// Get the intersection between the ray and the primitive
		bool Intersect(const Ray &r, SurfaceInteraction *surf = nullptr);
		
		// Get the surface area of the primitive
		float Area(); 
	public:
		// The shape attached to the primitive
		const Shape* shape;
};

}

#endif
