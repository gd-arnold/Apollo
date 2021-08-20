#ifndef APOLLO_MATH_VECTOR_3_H
#define APOLLO_MATH_VECTOR_3_H

#include "apollo.h"
#include "normal3.h"

namespace apollo {

template<class T> class Vector3 {
	public:
		Vector3() : x(0), y(0), z(0) {}
		Vector3(T u) : x(u), y(u), z(u) {}
		Vector3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}

		// Copy constructors
		Vector3(const Vector3<T> &v) : x(v.x), y(v.y), z(v.z) {}
		explicit Vector3(const Normal3<T> &n) : x(n.x), y(n.y), z(n.z) {}
		
		// Assignment operator
		Vector3<T>& operator=(const Vector3<T> &v) {
			x = v.x;
			y = v.y;
			z = v.z;
			return *this;
		}

		// Get by index
		T  operator[](int i) const {
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

		// Min and Max components
		T MinComponent() const {
			if (x < y && x < z)
				return x;
			if (y < x && y < z)
				return y;
			return z;
		}

		T MaxComponent() const {
			if (x > y && x > z)
				return x;
			if (y > x && y > z)
				return y;
			return z;
		}
		
		// Addition and subtraction
		Vector3<T> operator+(const Vector3<T> &v) const {
			return Vector3<T>(v.x+x, v.y+y, v.z+z);
		}

		Vector3<T>& operator+=(const Vector3<T> &v) {
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}

		Vector3<T> operator-(const Vector3<T> &v) const {
			return Vector3<T>(x-v.x, y-v.y, z-v.z);
		}

		Vector3<T>& operator-=(const Vector3<T> &v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}

		// Scalar multiplication and division
		Vector3<T>  operator*(const T s) const {
			return Vector3<T>(x*s, y*s, z*s);
		}

		Vector3<T>& operator*=(const T s) {
			x *= s;
			y *= s;
			z *= s;
			return *this;
		}

		Vector3<T>  operator/(const T s) const {
			float inv = 1.0 / s;
			return Vector3<T>(x*inv, y*inv, z*inv);
		}

		Vector3<T>& operator/=(const T s) {
			float inv = 1.0 / s;
			x *= inv;
			y *= inv;
			z *= inv;
			return *this;
		}

		// Vector negation
		Vector3<T> operator-() const {
			return Vector3<T>(-x, -y, -z);
		}

		// Length
		float LengthSquared() const {
			return x*x + y*y + z*z; 
		}

		float Length() const {
			return std::sqrt(lengthSquared());
		}

		// Absolute value
		Vector3<T> Abs() const {
			return Vector3<T>(std::abs(x), std::abs(y), std::abs(z));
		}

		// Normalization
		Vector3<T>  Normalized() const {
			float invLength = 1.0 / length();
			return Vector3<T>(x * invLength, y * invLength, z * invLength);
		}

		Vector3<T>& Normalize() {
			float invLength = 1.0 / length();
			x *= invLength;
			y *= invLength;
			z *= invLength;
			return *this;
		}	

		// Vector3 public data
		T x, y, z;

};

// Print
template <typename T> inline std::ostream& operator<<(std::ostream &out, const Vector3<T> &v) {
	return out << v.x << ' ' << v.y << ' ' << v.z;
}

// Scalar multiplication in case of s * v
template <typename T> inline Vector3<T> operator*(T s, const Vector3<T> &v) {
	return v * s;
}

// Dot product
template <typename T> inline T Dot(const Vector3<T> &v1, const Vector3<T> &v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; 
}

template <typename T> inline T Dot(const Vector3<T> &v1, const Normal3<T> &n1) {
	return v1.x * n1.x + v1.y * n1.y + v1.z * n1.z; 
}

template <typename T> inline T AbsDot(const Vector3<T> &v1, const Vector3<T> &v2) {
	return std::abs(dot(v1, v2));
}

template <typename T> inline T AbsDot(const Vector3<T> &v1, const Normal3<T> &n1) {
	return std::abs(dot(v1, n1));
}

// Cross products
template <typename T> inline Vector3<T> Cross(const Vector3<T> &v1, const Vector3<T> &v2) {
	double v1x = v1.x, v1y = v1.y, v1z = v1.z;
	double v2x = v2.x, v2y = v2.y, v2z = v2.z;
	return Vector3<T>((v1y * v2z) - (v1z * v2y), 
			  (v1z * v2x) - (v1x * v2z),
			  (v1x * v2y) - (v1y * v2x));
}

template <typename T> inline Vector3<T> Cross(const Vector3<T> &v1, const Normal3<T> &n1) {
	double v1x = v1.x, v1y = v1.y, v1z = v1.z;
	double n1x = n1.x, n1y = n1.y, n1z = n1.z;
	return Vector3<T>((v1y * n1z) - (v1z * n1y), 
			  (v1z * n1x) - (v1x * n1z),
			  (v1x * n1y) - (v1y * n1x));
}

// Compare vector
template <typename T> inline bool operator==(const Vector3<T> &v1, const Vector3<T> &v2) {
	return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

template <typename T> inline bool operator==(const Vector3<T> &v1, const Normal3<T> &n1) {
	return v1.x == n1.x && v1.y == n1.y && v1.z == n1.z;
}

template <typename T> inline bool operator!=(const Vector3<T> &v1, const Vector3<T> &v2) {
	return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z;
}

template <typename T> inline bool operator!=(const Vector3<T> &v1, const Normal3<T> &n1) {
	return v1.x != n1.x || v1.y != n1.y || v1.z != n1.z;
}

typedef Vector3<float> Vector3f;
typedef Vector3<int> Vector3i;

}

#endif
