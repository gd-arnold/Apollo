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
}
