#ifndef APOLLO_CORE_APOLLO_H
#define APOLLO_CORE_APOLLO_H

#include <iostream>
#include <cmath>
#include <limits>

namespace apollo {

// Global Forward Declarations
template <typename T> class Vector2;
template <typename T> class Vector3;
template <typename T> class Point2;
template <typename T> class Point3;
template <typename T> class Normal3;
template <typename T> class Bounds2;
template <typename T> class Bounds3;
class Ray;

// Global constants
static constexpr float Infinity = std::numeric_limits<float>::infinity();
}

#endif
