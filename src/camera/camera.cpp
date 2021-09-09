#include "apollo.h"
#include "camera.h"

namespace apollo {

Camera::Camera(Film& film, float fov, Point3f& pos, Point3f& look, Vector3f& up) : film(film), fov(fov), aspectRatio(film.resolution.x / film.resolution.y) {
	InitializeTransformations(pos, look, up);
}

void Camera::InitializeTransformations(Point3f& pos, Point3f& look, Vector3f& up) {
	worldToCamera = LookAt(pos, look, up);
	cameraToWorld = worldToCamera.Inverse();
}


Ray Camera::GenerateRay(float x, float y) {
	// Convert from raster to screen space 
	x = (2 * ((x + 0.5) / film.resolution.x) - 1) * tan(fov/2) * aspectRatio;
	y = (1 - 2 * ((y + 0.5) / film.resolution.y))  * tan(fov/2);

	Ray r(Point3f(0), Vector3f(x, y, -1).Normalized());

	// Returns ray in world space
	return cameraToWorld(r);
}

}
