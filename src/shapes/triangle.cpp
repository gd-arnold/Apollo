#include "apollo.h"
#include "triangle.h"
#include "vector3.h"

namespace apollo {

	Triangle::Triangle(const Transform* objectToWorld, const Transform* worldToObject, bool reverseOrientation,
		const Point3f v0, const Point3f v1, const Point3f v2)
		: Shape(objectToWorld, worldToObject, reverseOrientation), v0(v0), v1(v1), v2(v2) {}

	bool Triangle::Intersect(const Ray& ray, SurfaceInteraction* surf) const {
		// Transform ray to object space
		Ray r = (*worldToObject)(ray);

		// Apply Möller–Trumbore ray-triangle intersection algorithm
		//==========================================================
		Vector3f v0v1 = v1 - v0;
		Vector3f v0v2 = v2 - v0;
		Vector3f translation = r.o - v0;
		Vector3f pvec = Cross(r.d, v0v1);
		
		float det = Dot(pvec, v0v2);
		
		// If determinant is close to 0, the ray and the triangle are parallel
		if (det < Epsilon)
			return false;

		float invDet = 1 / det;
		Vector3f qvec = Cross(translation, v0v2) * invDet;

		// Compute barycentric coordinates
		float u = Dot(translation, pvec) * invDet;
		if (u < 0 || u > 1)
			return false;
		
		float v = Dot(r.d, qvec);
		if (v < 0 || u + v > 1)
			return false;

		// Initialize surface interaction (if defined)
		if (surf) {
			float tHit = Dot(v0v1, qvec) * invDet;
			Point3f p = r(tHit);

			// TODO: Compute triangle partial derivatives
			Vector3f dpdu(0);
			Vector3f dpdv(0);

			*surf = (*objectToWorld)(SurfaceInteraction(p, Point2f(u, v), -r.d, dpdu, dpdv, r.time, this));
		}

		return true;
	}

	Bounds3f Triangle::ObjectBound() const {
		return Bounds3f(v0, v1).Union(v2);
	}

	Bounds3f Triangle::WorldBound() const {
		return Bounds3f((*objectToWorld)(v0), (*objectToWorld)(v1)).Union((*objectToWorld)(v2));
	}

	float Triangle::Area() const {
		Vector3f v0v1 = v1 - v0;
		Vector3f v0v2 = v2 - v0;
		return Cross(v0v1, v0v2).Length() * 0.5;
	}

}