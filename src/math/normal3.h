#ifndef APOLLO_MATH_NORMAL_3_H
#define APOLLO_MATH_NORMAL_3_H

#include "apollo.h"
#include "vector3.h"

namespace apollo {

template<class T> class Normal3 {
	public:
		Normal3() : x(0), y(0), z(0) {}
		Normal3(T u) : x(u), y(u), z(u) {}
		Normal3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}

		// Copy constructors
		Normal3(const Normal3<T> &n) : x(n.x), y(n.y), z(n.z) {}
		explicit Normal3(const Vector3<T> &v) : x(v.x), y(v.y), z(v.z)  {}
		
		// Assignment operator
		Normal3<T>& operator=(const Normal3<T> &n) {
			x = n.x;
			y = n.y;
			z = n.z;
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
		Normal3<T> operator+(const Normal3<T> &n) const {
			return Normal3<T>(n.x + x, n.y + y, n.z + z);
		}

		Normal3<T>& operator+=(const Normal3<T> &n) {
			x += n.x;
			y += n.y;
			z += n.z;
			return *this;
		}

		Normal3<T> operator-(const Normal3<T> &n) const {
			return Normal3<T>(x - n.x, y - n.y, z - n.z);
		}

		Normal3<T>& operator-=(const Normal3<T> &n) {
			x -= n.x;
			y -= n.y;
			z -= n.z;
			return *this;
		}

		// Scalar multiplication and division
		Normal3<T>  operator*(const T s) const {
			return Normal3<T>(x*s, y*s, z*s);
		}

		Normal3<T>& operator*=(const T s) {
			x *= s;
			y *= s;
			z *= s;
			return *this;
		}

		Normal3<T>  operator/(const T s) const {
			float inv = 1.0 / s;
			return Normal3<T>(x*inv, y*inv, z*inv);
		}

		Normal3<T>& operator/=(const T s) {
			float inv = 1.0 / s;
			x *= inv;
			y *= inv;
			z *= inv;
			return *this;
		}

		// Normal negation
		Normal3<T> operator-() const {
			return Normal3<T>(-x, -y, -z);
		}

		Normal3<T>& operator-() {
			return *this *= -1;
		}

		// Length
		float LengthSquared() const {
			return x*x + y*y + z*z; 
		}

		float Length() const {
			return std::sqrt(lengthSquared());
		}

		// Absolute value
		Normal3<T> Abs() const {
			return Normal3<T>(std::abs(x), std::abs(y), std::abs(z));
		}

		// Normalization
		Normal3<T>  Normalized() const {
			float invLength = 1.0 / length();
			return Normal3<T>(x * invLength, y * invLength, z * invLength);
		}

		Normal3<T>& Normalize() {
			float invLength = 1.0 / length();
			x *= invLength;
			y *= invLength;
			z *= invLength;
			return *this;
		}


		// Flip a surface normal so that it lies in the same hemisphere as a given vector/normal
		Normal3<T>& FaceForward(const Normal3<T> &n) {
			return dot(*this, n) < 0 ? -*this : *this;
		}

		Normal3<T>& FaceForward(const Vector3<T> &v) {
			return dot(*this, v) < 0 ? -*this : *this;
		}

		// Normal3 public data
		T x, y, z;

};

// Print
template <typename T> inline std::ostream& operator<<(std::ostream &out, const Normal3<T> &n) {
	return out << n.x << ' ' << n.y << ' ' << n.z; 
}

// Scalar multiplication in case of s * n
template <typename T> inline Normal3<T> operator*(T s, const Normal3<T> &n) {
	return n * s;
}

// Dot products
template <typename T> inline T Dot(const Normal3<T> &n1, const Normal3<T> &n2) {
	return n1.x * n2.x + n1.y * n2.y + n1.z * n2.z;
}

template <typename T> inline T Dot(const Normal3<T> &n1, const Vector3<T> &v1) {
	return n1.x * v1.x + n1.y * v1.y + n1.z * v1.z;
}

template <typename T> inline T AbsDot(const Normal3<T> &n1, const Normal3<T> &n2) {
	return std::abs(dot(n1, n2));
}

template <typename T> inline T AbsDot(const Normal3<T> &n1, const Vector3<T> &v1) {
	return std::abs(dot(n1, v1));
}

// Cross product
template <typename T> inline Normal3<T> cross(const Normal3<T> &n1, const Vector3<T> &v1) {
	double n1x = n1.x, n1y = n1.y, n1z = n1.z;
	double v1x = v1.x, v1y = v1.y, v1z = v1.z;
	return Normal3<T>((n1y * v1z) - (n1z * v1y), 
			  (n1z * v1x) - (n1x * v1z),
			  (n1x * v1y) - (n1y * v1x));
}

// Compare normal
template <typename T> inline bool operator==(const Normal3<T> &n1, const Normal3<T> &n2) {
	return n1.x == n2.x && n1.y == n2.y && n1.z == n2.z;
}

template <typename T> inline bool operator==(const Normal3<T> &n1, const Vector3<T> &v1) {
	return n1.x == v1.x && n1.y == v1.y && n1.z == v1.z;
}

template <typename T> inline bool operator!=(const Normal3<T> &n1, const Normal3<T> &n2) {
	return n1.x != n2.x || n1.y != n2.y || n1.z != n2.z;
}

template <typename T> inline bool operator!=(const Normal3<T> &n1, const Vector3<T> &v1) {
	return n1.x != v1.x || n1.y != v1.y || n1.z != v1.z;
}

typedef Normal3<float> Normal3f;
typedef Normal3<int> Normal3i;

}

#endif
