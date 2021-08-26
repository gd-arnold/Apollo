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
		
		// Accessor methods
		const Point3f& p() const;
		Point3f& p();
		const float& time() const;
		float time();
		const Vector3f& wo() const;
		Vector3f& wo();
		const Normal3f& n() const;
		Normal3f& n();

	protected:
		// Intersection point
		Point3f _p;
		// Time of intersection
		float _time;
		// Negative ray direction
		Vector3f _wo;
		// Surface normal
		Normal3f _n;
};

// SurfaceInteraction entity represents local information at a point on a surface
class SurfaceInteraction : public Interaction {
	public:
		SurfaceInteraction(const Point3f &p, const Point2f &uv, const Vector3f &wo,
				   const Vector3f &dpdu, const Vector3f &dpdv,
				   const Vector3f &dndu, const Vector3f &dndv,
				   float time, const Shape *shape);

		// Accessor methods
		const Point2f& uv() const;
		Point2f& uv();
		const Vector3f& dpdu() const;
		Vector3f& dpdu();
		const Vector3f& dpdv() const;
		Vector3f& dpdv();
		const Normal3f& dndu() const;
		Normal3f& dndu();
		const Normal3f& dndv() const;
		Normal3f& dndv();

	private:
		// (u,v) coords from the parameterization of the surface
		Point2f _uv;
		// Parametric partial derivatives of the point and surface normal
		Vector3f _dpdu, _dpdv;
		Normal3f _dndu, _dndv;
	public:
		// The shape that the point lies on
		const Shape *shape = nullptr;
};

}
#endif
