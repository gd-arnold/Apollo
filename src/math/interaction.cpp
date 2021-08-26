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

	SurfaceInteraction::SurfaceInteraction(const Point3f &p, const Point2f &uv, const Vector3f &wo,
		const Vector3f &dpdu, const Vector3f &dpdv,          
		const Vector3f &dndu, const Vector3f &dndv,       
		float time, const Shape *shape) : Interaction(p, Normal3f(Cross(dpdu, dpdv)), wo, time),
		_uv(uv), _dpdu(dpdu), _dpdv(dpdv), _dndu(dndu), _dndv(dndv), shape(shape) {
		// Swap normal direction if shape has reverse orientation or 
		// object to world transformation changes coordinate system handedness
		if (shape && (shape->reverseOrientation ^ shape->transformChangesHandedness))
			_n *= -1;	
	}

	// Accessor methods
	const Point2f& SurfaceInteraction::uv() const { return _uv; }
	Point2f& SurfaceInteraction::uv() { return _uv; }
	const Vector3f& SurfaceInteraction::dpdu() const { return _dpdu; }	
	Vector3f& SurfaceInteraction::dpdu() { return _dpdu; }
	const Vector3f& SurfaceInteraction::dpdv() const { return _dpdv; }	
	Vector3f& SurfaceInteraction::dpdv() { return _dpdv; }
	const Normal3f& SurfaceInteraction::dndu() const { return _dndu; }		
	Normal3f& SurfaceInteraction::dndu() { return _dndu; }
	const Normal3f& SurfaceInteraction::dndv() const { return _dndv; }	
	Normal3f& SurfaceInteraction::dndv() { return _dndv; }
}
