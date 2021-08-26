#ifndef APOLLO_MATH_INTERACTION_H
#define APOLLO_MATH_INTERACTION_H

#include "point3.h"
#include "point2.h"
#include "normal3.h"
#include "vector3.h"
#include "shape.h"

namespace apollo {

class Interaction {
	public:
		Interaction(const Point3f &p, const Normal3f &n, const Vector3f &wo, float time);
	protected:
		// Intersection point
		Point3f p;
		// Time of intersection
		float time;
		// Negative ray direction
		Vector3f wo;
		// Surface normal
		Normal3f n;
};

// SurfaceInteraction entity represents local information at a point on a surface
class SurfaceInteraction : public Interaction {
	public:
		SurfaceInteraction(const Point3f &p, const Point2f &uv, const Vector3f &wo,
				   const Vector3f &dpdu, const Vector3f &dpdv,
				   const Vector3f &dndu, const Vector3f &dndv,
				   float time, const Shape *shape);

	private:
		// (u,v) coords from the parameterization of the surface
		Point2f uv;
		// Parametric partial derivatives of the point and surface normal
		Vector3f dpdu, dpdv;
		Normal3f dndu, dndv;
		// The shape that the point lies on
		const Shape *shape = nullptr;
};

}
#endif
