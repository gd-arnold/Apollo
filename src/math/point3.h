#ifndef APOLLO_MATH_POINT_3_H
#define APOLLO_MATH_POINT_3_H

#include "apollo.h"
#include "vector3.h"

namespace apollo {

template<class T> class Point3 {
	public:
		Point3() : x(0), y(0), z(0) {}
		Point3(T u) : x(u), y(u), z(u) {}
		Point3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}

		// Copy constructor
		Point3(const Point3<T> &p) : x(p.x), y(p.y), z(p.z) {}

		// Point type conversion
		template <typename U> explicit Point3(const Point3<U> &p) 
			: x((T)p.x), y((T)p.y), z((T)p.z) {}

		// Assignment operator
		Point3<T>& operator=(const Point3<T> &p) {
			x = p.x;
			y = p.y;
			z = p.z;
			return *this;
		}

		// Array indexing to select between point components
		T operator[](int i) const {
			if (i == 0)
				return x;
			if (i == 1)
				return y;
			return z;
		}

		T& operator[](int i) {
			if (i == 0)
				return x;
			if (i == 1)
				return y;
			return z;
		}

		// Point addition
		Point3<T> operator+(const Point3<T> &p) const {
			return Point3<T>(x + p.x, y + p.y, z + p.z);
		}

		Point3<T>& operator+=(const Point3<T> &p) {
			x += p.x;
			y += p.y;
			z += p.z;
			return *this;
		}
		
		// Scalar addition, subtraction and multiplication
		Point3<T> operator+(T s) const {
			return Point3<T>(x + s, y + s, z + s);
		}

		Point3<T>& operator+=(T s) const {
			x += s;
			y += s;
			z += s;
			return *this;
		}

		Point3<T> operator-(T s) const {
			return Point3<T>(x - s, y - s, z - s);
		}

		Point3<T>& operator-=(T s) const {
			x -= s;
			y -= s;
			z -= s;
			return *this;
		}

		Point3<T> operator*(T s) const {
			return Point3<T>(x * s, y * s, z * s);
		}

		Point3<T>& operator*=(T s) {
			x *= s;
			y *= s;
			z *= s;
			return *this;
		}

		// Vector addition and subtraction from a point
		Point3<T> operator+(const Vector3<T> &v) const {
			return Point3<T>(x + v.x, y + v.y, z + v.z);
		}

		Point3<T>& operator+=(const Vector3<T> &v) {
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}

		Point3<T> operator-(const Vector3<T> &v) const {
			return Point3<T>(x - v.x, y - v.y, z - v.z);
		}

		Point3<T>& operator-=(const Vector3<T> &v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}

		// Subtract two points (obtaining the vector between them)
		Vector3<T> operator-(const Point3<T> &p) const {
			return Vector3<T>(x - p.x, y - p.y, z - p.z);
		}

		// Point3 public data
		T x, y, z;
};

// Print
template <typename T> inline std::ostream& operator<<(std::ostream &out, const Point3<T> &p) {
	return out << p.x << ' ' << p.y << ' ' << p.z;
}

// Scalar multiplication in case of s * p
template <typename T> inline Point3<T> operator*(T s, const Point3<T> &p) {
	return Point3<T>(p.x * s, p.y * s, p.z * s);
}

// Distance between two points
template <typename T> inline float Distance(const Point3<T> &p1, const Point3<T> &p2) {
	return (p1 - p2).Length();
}

template<typename T> inline float DistanceSquared(const Point3<T> &p1, const Point3<T> &p2) {
	return (p1 - p2).LengthSquared();
}

// Linear interpolation
template<typename T> inline Point3<T> Lerp(float t, const Point3<T> &p1, const Point3<T> &p2) {
	return (1 - t) * p1 + t * p2;
}

typedef Point3<float> Point3f;
typedef Point3<int> Point3i;

}

#endif
