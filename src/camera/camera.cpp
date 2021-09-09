#include "apollo.h"
#include "camera.h"

namespace apollo {

Camera::Camera(Film& film, float fov) : film(film), fov(fov), aspectRatio(film.resolution.x / film.resolution.y) {}


Ray Camera::GenerateRay(float x, float y) {
	// Convert from raster to screen space 
	x = (2 * ((x + 0.5) / film.resolution.x) - 1) * tan(fov/2) * aspectRatio;
	y = (1 - 2*((y + 0.5) / film.resolution.y))  * tan(fov/2);

	Ray r(Point3f(0), Vector3f(x, y, -1).Normalized());

	// TODO Apply camera look-at transformation

	return r;
}

}
