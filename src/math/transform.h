#ifndef MATH_APOLLO_TRANSFORM_H
#define MATH_APOLLO_TRANSFORM_H

#include "apollo.h"
#include "matrix.h"
#include "vector3.h"

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
}

#endif
