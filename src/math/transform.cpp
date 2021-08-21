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

}
