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
		Camera(Film& film, float fov);

		// Generate a primary ray given film (x, y) coordinates
		Ray GenerateRay(float x, float y);
	private:
		const Film film;
		
		// Image aspect ratio (width / height)
		const float aspectRatio;
		
		// Camera field of view (in radians)
		const float fov;
	
		// Transformation from camera to world space
		const Transform worldToCamera;
		const Transform cameraToWorld;
};

}

#endif
