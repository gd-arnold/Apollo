#include "primitive.h"

namespace apollo {

// Primitive Definitions
// =====================

Primitive::Primitive(const Shape* shape) : shape(shape) {}

// Get the axis aligned bounding box of the primitive in world space
Bounds3f Primitive::WorldBound() {
	return shape->WorldBound();
}

// Get the intersection between the ray and the primitive
bool Primitive::Intersect(const Ray &r, SurfaceInteraction *surf) {
	bool intersection = shape->Intersect(r, surf);
	if (intersection && surf) {
		surf->primitive = this;
		return true;
	}

	return intersection;
}

// Get the surface area of the primitive
float Primitive::Area() {
	return shape->Area();
}

}
