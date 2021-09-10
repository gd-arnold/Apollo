#include "apollo.h"
#include "imageio.h"

namespace apollo {

// Write film pixels to .ppm file
bool WriteToPPM(Film& film) {
	int width = film.resolution.x; // 400
	int height = film.resolution.y; // 600

	std::cout << "P3\n" << width << " " << height << "\n255\n";

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::cout << film.GetPixel(Point2i(i, j)) << '\n';
		}
	}

	return true;
}

}
