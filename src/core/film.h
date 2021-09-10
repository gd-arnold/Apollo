#ifndef APOLLO_CORE_FILM_H
#define APOLLO_CORE_FILM_H

#include "apollo.h"
#include "point2.h"
#include "rgb.h"

namespace apollo {

// Film class represents the sensing device in the simulated camera
class Film {
	public:
		Film(const Point2i& res);
	
		RGB const & GetPixel(const Point2i& position) const;
		RGB& GetPixel(const Point2i& position);
	public:
		const Point2i resolution;
	private:
		std::shared_ptr<RGB[]> pixels{new RGB[resolution.x * resolution.y]};

};

}

#endif
