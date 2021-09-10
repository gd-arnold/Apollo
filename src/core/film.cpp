#include "film.h"

namespace apollo {

Film::Film(const Point2i& res) : resolution(res) {}

RGB const & Film::GetPixel(const Point2i& position) const {
	return pixels[position.x * resolution.x + position.y];
}

RGB& Film::GetPixel(const Point2i& position) {
	return pixels[position.x * resolution.x + position.y];
}

}
