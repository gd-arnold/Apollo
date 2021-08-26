#include "interaction.h"

namespace apollo {
	
	Interaction::Interaction(const Point3f &p, const Normal3f &n, const Vector3f &wo, float time) 
				: p(p), n(n), wo(wo), time(time) {}

	SurfaceInteraction::SurfaceInteraction(const Point3f &p, const Point2f &uv, const Vector3f &wo,
		const Vector3f &dpdu, const Vector3f &dpdv,          
		const Vector3f &dndu, const Vector3f &dndv,       
		float time, const Shape *shape) : Interaction(p, Normal3f(Cross(dpdu, dpdv)), wo, time),
		uv(uv), dpdu(dpdu), dpdv(dpdv), dndu(dndu), dndv(dndv), shape(shape) {
		// Swap normal direction if shape has reverse orientation or 
		// object to world transformation changes coordinate system handedness
		if (shape && (shape->reverseOrientation ^ shape->transformChangesHandedness))
			n *= -1;	
	}
	

}
