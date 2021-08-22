#ifndef MATH_APOLLO_TRANSFORM_H
#define MATH_APOLLO_TRANSFORM_H

#include "apollo.h"
#include "matrix.h"
#include "vector3.h"
#include "point3.h"
#include "normal3.h"
#include "ray.h"

namespace apollo {

class Transform {
	public:
		Transform() {}
		Transform(const Matrix& m);
		Transform(const Matrix& m, const Matrix& mInv);

		Matrix GetMatrix() const;
		Matrix GetInversedMatrix() const;

		// Get inversed transformation by swapping the two matricies
		Transform Inverse() const;

		// Get transposed transformation by transposing the two matricies
		Transform Transpose() const;

		// Apply transformation to geometries
		// ==================================
		template <typename T> inline Point3<T>  operator()(const Point3<T>& p)  const;
		template <typename T> inline Vector3<T> operator()(const Vector3<T>& v) const;
		template <typename T> inline Normal3<T> operator()(const Normal3<T>& n) const;
		inline Ray operator()(const Ray& r) const;

	private:
		// Transform private data
		// Matrix and Inverse matrix of the transformation
		Matrix m;
		Matrix mInv;
};

// Common Transformations
// ======================
// Translation transformation
Transform Translate(Vector3f &v);
// Scale transformation
Transform Scale(float x, float y, float z);
// X, Y and Z axis clockwise rotation transformations
Transform RotateX(float theta);
Transform RotateY(float theta);
Transform RotateZ(float theta);
// Camera Look-at transformation (used to convert from camera to world space)
Transform LookAt(const Point3f& pos, const Point3f& look, const Vector3f& up);

// Apply transformation to geometries
// ==================================
template <typename T> inline Point3<T> Transform::operator()(const Point3<T>& p) const {
	const T x = m.m[0]*p.x + m.m[1]*p.y + m.m[2]*p.z + m.m[3];
	const T y = m.m[4]*p.x + m.m[5]*p.y + m.m[6]*p.z + m.m[7];
	const T z = m.m[8]*p.x + m.m[9]*p.y + m.m[10]*p.z + m.m[11];
	const T weight = m.m[12]*p.x + m.m[13]*p.y + m.m[14]*p.z + m.m[15];

	return weight == 1 ? Point3<T>(x, y, z) : Point3<T>(x, y, z) * (1.0f / weight);
}

template <typename T> inline Vector3<T> Transform::operator()(const Vector3<T>& v) const {
	const T x = m.m[0]*v.x + m.m[1]*v.y + m.m[2]*v.z;
	const T y = m.m[4]*v.x + m.m[5]*v.y + m.m[6]*v.z;
	const T z = m.m[8]*v.x + m.m[9]*v.y + m.m[10]*v.z;

	return Vector3<T>(x, y, z);
}

template <typename T> inline Normal3<T> Transform::operator()(const Normal3<T>& n) const {
	Matrix newM = mInv.Transpose();

	const T x = newM.m[0]*n.x + newM.m[1]*n.y + newM.m[2]*n.z;
	const T y = newM.m[4]*n.x + newM.m[5]*n.y + newM.m[6]*n.z;
	const T z = newM.m[8]*n.x + newM.m[9]*n.y + newM.m[10]*n.z;

	return Normal3<T>(x, y, z);
}

inline Ray Transform::operator()(const Ray& r) const {
	return Ray((*this)(r.o), (*this)(r.d), r.tMax, r.time);
}

}

#endif
