#ifndef APOLLO_MATH_VECTOR_2_H
#define APOLLO_MATH_VECTOR_2_H

#include "apollo.h"

namespace apollo {

template<class T> class Vector2 {
	public:
		Vector2() : x(0), y(0) {}
		Vector2(T u) : x(u), y(u) {}
		Vector2(T xx, T yy) : x(xx), y(yy) {}

		// Copy constructor
		Vector2(const Vector2<T> &v) : x(v.x), y(v.y) {}
		
		// Assignment operator
		Vector2<T>& operator=(const Vector2<T> &v) {
			x = v.x;
			y = v.y;
			return *this;
		}
		
		// Get by index
		T  operator[](int i) const {
			return i == 0 ? x : y;
		}
		
		T& operator[](int i) {
			return i == 0 ? x : y;
		}

		// Min and Max components
		T MinComponent() const {
			return x < y ? x : y;
		}

		T MaxComponent() const {
			return x > y ? x : y;
		}
		
		// Addition and subtraction
		Vector2<T> operator+(const Vector2<T> &v) const {
			return Vector2<T>(v.x+x, v.y+y);
		}

		Vector2<T>& operator+=(const Vector2<T> &v) {
			x += v.x;
			y += v.y;
			return *this;
		}

		Vector2<T> operator-(const Vector2<T> &v) const {
			return Vector2<T>(x-v.x, y-v.y);
		}

		Vector2<T>& operator-=(const Vector2<T> &v) {
			x -= v.x;
			y -= v.y;
			return *this;
		}

		// Scalar multiplication and division
		Vector2<T>  operator*(const T s) const {
			return Vector2<T>(x*s, y*s);
		}

		Vector2<T>& operator*=(const T s) {
			x *= s;
			y *= s;
			return *this;
		}

		Vector2<T>  operator/(const T s) const {
			float inv = 1.0 / s;
			return Vector2<T>(x*inv, y*inv);
		}

		Vector2<T>& operator/=(const T s) {
			float inv = 1.0 / s;
			x *= inv;
			y *= inv;
			return *this;
		}

		// Vector negation
		Vector2<T> operator-() const {
			return Vector2<T>(-x, -y);
		}

		// Length
		float LengthSquared() const {
			return x*x + y*y; 
		}

		float Length() const {
			return std::sqrt(LengthSquared());
		}

		// Absolute value
		Vector2<T> Abs() const {
			return Vector2<T>(std::abs(x), std::abs(y));
		}

		// Normalization
		Vector2<T>  Normalized() const {
			float invLength = 1.0 / Length();
			return Vector2<T>(x * invLength, y * invLength);
		}

		Vector2<T>& Normalize() {
			float invLength = 1.0 / Length();
			x *= invLength;
			y *= invLength;
			return *this;
		}

		// Vector2 public data
		T x, y;

};

// Print
template <typename T> inline std::ostream& operator<<(std::ostream &out, const Vector2<T> &v) {
	return out << v.x << ' ' << v.y;
}

// Scalar multiplication in case of s * v
template <typename T> inline Vector2<T> operator*(T s, const Vector2<T> &v) {
	return v * s;	
}

// Dot product
template <typename T> inline T Dot(const Vector2<T> &v1, const Vector2<T> &v2) {
	return v1.x * v2.x + v1.y * v2.y; 
}

template <typename T> inline T AbsDot(const Vector2<T> &v1, const Vector2<T> &v2) {
	return std::abs(dot(v1, v2));
}

// Compare vectors
template <typename T> inline bool operator==(const Vector2<T> &v1, const Vector2<T> &v2) {
	return v1.x == v2.x && v1.y == v2.y;
}

template <typename T> inline bool operator!=(const Vector2<T> &v1, const Vector2<T> &v2) {
	return v1.x != v2.x || v1.y != v2.y;
}

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;

}

#endif
