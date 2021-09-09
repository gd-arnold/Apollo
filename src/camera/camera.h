#ifndef APOLLO_CAMERA_CAMERA_H
#define APOLLO_CAMERA_CAMERA_H

#include "apollo.h"
#include "ray.h"
#include "transform.h"
#include "film.h"

namespace apollo {

// Perspective camera model
class Camera {
	public:
		Camera(Film& film, float fov, Point3f& pos, Point3f& look, Vector3f& up);

		// Generate primary ray in world space given film (x, y) coordinates
		Ray GenerateRay(float x, float y);
	private:

		void InitializeTransformations(Point3f& pos, Point3f& look, Vector3f& up);

		const Film film;
		
		// Image aspect ratio (width / height)
		const float aspectRatio;
		
		// Camera field of view (in radians)
		const float fov;
	
		// Transformation from world to camera space and vice versa
		Transform worldToCamera;
		Transform cameraToWorld;
};

}

#endif
