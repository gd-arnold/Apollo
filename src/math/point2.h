#ifndef APOLLO_MATH_POINT_2_H
#define APOLLO_MATH_POINT_2_H

#include "apollo.h"
#include "vector2.h"
#include "point3.h"

namespace apollo {

template<class T> class Point2 {
	public:
		Point2() : x(0), y(0) {}
		Point2(T u) : x(u), y(u) {}
		Point2(T xx, T yy) : x(xx), y(yy) {}

		// Copy constructor
		Point2(const Point2<T> &p) : x(p.x), y(p.y) {}

		// Point3 to Point2 conversion
		explicit Point2(const Point3<T> &p) : x(p.x), y(p.y) {}

		// Point type conversion
		template <typename U> explicit Point2(const Point2<U> &p) 
			: x((T)p.x), y((T)p.y) {}

		// Assignment operator
		Point2<T>& operator=(const Point2<T> &p) {
			x = p.x;
			y = p.y;
			return *this;
		}

		// Addition and scalar multiplication
		Point2<T> operator+(const Point2<T> &p) const {
			return Point2<T>(x + p.x, y + p.y);
		}

		Point2<T>& operator+=(const Point2<T> &p) {
			x += p.x;
			y += p.y;
			return *this;
		}

		Point2<T> operator*(T s) const {
			return Point2<T>(x * s, y * s);
		}

		Point2<T>& operator*=(T s) {
			x *= s;
			y *= s;
			return *this;
		}

		// Vector addition and subtraction from a point
		Point2<T> operator+(const Vector2<T> &v) const {
			return Point2<T>(x + v.x, y + v.y);
		}

		Point2<T>& operator+=(const Vector2<T> &v) {
			x += v.x;
			y += v.y;
			return *this;
		}

		Point2<T> operator-(const Vector2<T> &v) const {
			return Point2<T>(x - v.x, y - v.y);
		}

		Point2<T>& operator-=(const Vector2<T> &v) {
			x -= v.x;
			y -= v.y;
			return *this;
		}

		// Subtract two points (obtaining the vector between them)
		Vector2<T> operator-(const Point2<T> &p) const {
			return Vector2<T>(x - p.x, y - p.y);
		}

		// Point2 public data
		T x, y;
};

// Print
template <typename T> inline std::ostream& operator<<(std::ostream &out, const Point2<T> &p) {
	return out << p.x << ' ' << p.y;
}

// Scalar multiplication in case of s * p
template <typename T> inline Point2<T> operator*(T s, const Point2<T> &p) {
	return Point2<T>(p.x * s, p.y * s);
}

// Distance between two points
template <typename T> inline float Distance(const Point2<T> &p1, const Point2<T> &p2) {
	return (p1 - p2).Length();
}

template<typename T> inline float DistanceSquared(const Point2<T> &p1, const Point2<T> &p2) {
	return (p1 - p2).LengthSquared();
}

// Linear interpolation
template<typename T> inline Point2<T> Lerp(float t, const Point2<T> &p1, const Point2<T> &p2) {
	return (1 - t) * p1 + t * p2;
}

typedef Point2<float> Point2f;
typedef Point2<int> Point2i;

}

#endif
