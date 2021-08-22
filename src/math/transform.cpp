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

}
