#include "apollo.h"
#include "transform.h"

namespace apollo {

Transform::Transform(const Matrix& m) {
	this->m = m;
	m.Inverse(mInv);
}

Transform::Transform(const Matrix& m, const Matrix& mInv) : m(m), mInv(mInv) {}

Matrix Transform::GetMatrix() const {
	return m;
}

Matrix Transform::GetInversedMatrix() const {
	return mInv;
}

// Get inversed transformation by swapping the two matricies
Transform Transform::Inverse() const {
	return Transform(mInv, m);
}

// Get transposed transformation by transposing the two matricies
Transform Transform::Transpose() const {
	return Transform(m.Transpose(), mInv.Transpose());
}

// Check if a transformation changes coordinate system handedness
bool Transform::ChangesHandedness() const {
	return m.Determinant3x3() < 0.0f;
}

// Translation transformation
Transform Translate(Vector3f &v) {
	Matrix m(1, 0, 0, v.x,
		 0, 1, 0, v.y,
		 0, 0, 1, v.z,
		 0, 0, 0, 1);

	Matrix mInv(1, 0, 0, -v.x,
		    0, 1, 0, -v.y,
		    0, 0, 1, -v.z,
		    0, 0, 0, 1);

	return Transform(m, mInv);
}

// Scale transformation
Transform Scale(float x, float y, float z) {
	Matrix m(x, 0, 0, 0,
		 0, y, 0, 0,
		 0, 0, z, 0,
		 0, 0, 0, 1);

	Matrix mInv(1.0f/x, 0, 0, 0,
		    0, 1.0f/y, 0, 0,
		    0, 0, 1.0f/z, 0,
		    0, 0, 0, 1);

	return Transform(m, mInv);
}

// X, Y and Z axis clockwise rotation transformations
Transform RotateX(float theta) {
	float sinTheta = std::sin(theta);
	float cosTheta = std::cos(theta);

	Matrix m(1, 	   0, 	      0, 0,
		 0, cosTheta, -sinTheta, 0,
		 0, sinTheta,  cosTheta, 0,
		 0,	   0, 	      0, 1);
	
	return Transform(m, m.Transpose());
}

Transform RotateY(float theta) {
	float sinTheta = std::sin(theta);
	float cosTheta = std::cos(theta);

	Matrix m(cosTheta,  0, sinTheta, 0,
		 0, 	    1, 0, 	 0,
		 -sinTheta, 0, cosTheta, 0,
		 0, 	    0, 0, 	 1);
	
	return Transform(m, m.Transpose());
}

Transform RotateZ(float theta) {
	float sinTheta = std::sin(theta);
	float cosTheta = std::cos(theta);

	Matrix m(cosTheta, -sinTheta, 0, 0,
		 sinTheta,  cosTheta, 0, 0,
		 0,	    0,	      1, 0,
		 0,	    0,	      0, 1);

	return Transform(m, m.Transpose());
}

// Camera Look-at transformation 
Transform LookAt(const Point3f& pos, const Point3f& look, const Vector3f& up) {
	// Define camera basis
	const Vector3f dir = (look - pos).Normalized();
	const Vector3f right = Cross(up.Normalized(), dir).Normalized();
	const Vector3f adjustedUp = Cross(dir, right);

	Matrix mInv;
	Matrix m(right.x, adjustedUp.x,	dir.x, 	pos.x,
	  	 right.y, adjustedUp.y, dir.y,  pos.y,
	  	 right.z, adjustedUp.z, dir.z,	pos.z,
	  	 0,	  0,	  	0,	1);

	m.Inverse(mInv);

	return Transform(mInv, m); 

}

// Apply transformation to geometries
// ==================================
SurfaceInteraction Transform::operator()(const SurfaceInteraction& s) const {
	const Transform &t = *this;	
	
	SurfaceInteraction result;
	result.p() = t(s.p());
	result.time() = s.time();
	result.n() = t(s.n()).Normalize();
	result.wo() = t(s.wo());
	result.uv() = s.uv();

	return result;
}

// Transformations composition 
Transform Transform::operator*(const Transform& t) const {
	return Transform(m * t.m, t.mInv * mInv);
}

}
