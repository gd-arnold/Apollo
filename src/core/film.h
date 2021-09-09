#ifndef APOLLO_CORE_FILM_H
#define APOLLO_CORE_FILM_H

#include "apollo.h"
#include "point2.h"

namespace apollo {

// Film class represents the sensing device in the simulated camera
class Film {
	public:
		Film(Point2i resolution);		
	public:
		const Point2i resolution;
};

}

#endif
