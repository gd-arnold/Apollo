#ifndef APOLLO_CORE_IMAGEIO_H
#define APOLLO_CORE_IMAGEIO_H

#include "apollo.h"
#include "film.h"

namespace apollo {

// Write film pixels to .ppm file
bool WriteToPPM(Film& film);

}

#endif
