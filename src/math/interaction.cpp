#include "interaction.h"

namespace apollo {
	
	Interaction::Interaction(const Point3f &p, const Normal3f &n, const Vector3f &wo, float time) 
				: _p(p), _n(n), _wo(wo), _time(time) {}
	
	// Accessor methods
	const Point3f& Interaction::p() const { return _p; }
	Point3f& Interaction::p() { return _p; }
	const float& Interaction::time() const { return _time; }
	float& Interaction::time() { return _time; }
	const Vector3f& Interaction::wo() const { return _wo; }
	Vector3f& Interaction::wo() { return _wo; }
	const Normal3f& Interaction::n() const { return _n; }
	Normal3f& Interaction::n() { return _n; }

	SurfaceInteraction::SurfaceInteraction(const Point3f& p, const Normal3f& n, const Point2f& uv, const Vector3f& wo,          
		float time, const Shape *shape) : Interaction(p, n, wo, time),
		_uv(uv), shape(shape) {
		// Swap normal direction if shape has reverse orientation or 
		// object to world transformation changes coordinate system handedness
		if (shape && (shape->reverseOrientation ^ shape->transformChangesHandedness))
			_n *= -1;	
	}

	// Accessor methods
	const Point2f& SurfaceInteraction::uv() const { return _uv; }
	Point2f& SurfaceInteraction::uv() { return _uv; }
}
