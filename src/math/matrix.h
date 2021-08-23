#include "apollo.h"
#include "stringprint.h"

#ifndef APOLLO_MATH_MATRIX_H
#define APOLLO_MATH_MATRIX_H

namespace apollo {
// 4x4 Matrix
class Matrix {
	public:
		// Default constructor; Initializes 4x4 identity matrix 
		Matrix();

		// Constructor from an array of 16 floats
		Matrix(const float mat[16]);

		// Constructor from 16 floats
		Matrix(float t00, float t01, float t02, float t03,
		       float t10, float t11, float t12, float t13,
		       float t20, float t21, float t22, float t23,
		       float t30, float t31, float t32, float t33);

		// Matrix multiplication
		Matrix  operator* (const Matrix& mat) const;

		// Matrix determinant
		float Determinant() const;

		// Upper-left 3x3 submatrix determinant
		float Determinant3x3() const;
		// Matrix transpose
		Matrix Transpose() const;
			
		// Matrix inverse
		bool Inverse(Matrix& out) const;

		// 4x4 Matrix public data
		// m[0]  m[1]  m[2]  m[3]
		// m[4]  m[5]  m[6]  m[7]
		// m[8]  m[9]  m[10] m[11]
		// m[12] m[13] m[14] m[15]
		float m[16];
};

// Print Matrix
std::ostream& operator<<(std::ostream& out, const Matrix& mat); 

}

#endif
