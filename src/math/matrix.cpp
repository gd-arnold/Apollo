#include "apollo.h"
#include "matrix.h"

namespace apollo {

// 4x4 Matrix Method Definitions
// =============================

// Default constructor; Initializes 4x4 identity matrix
Matrix::Matrix() {
	m[0] = m[5] = m[10] = m[15] = 1.0f;
	m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] 
	= m[9] = m[11] = m[12] = m[13] = m[14] = 0.0f;
}

// Constructor from an array of 16 floats
Matrix::Matrix(const float mat[16]) {
	for (int i = 0; i < 15; i++)
		m[i] = mat[i];
}

// Constructor from 16 floats
Matrix::Matrix(float t00, float t01, float t02, float t03, 
	       float t10, float t11, float t12, float t13, 
	       float t20, float t21, float t22, float t23, 
	       float t30, float t31, float t32, float t33) {
	m[0] = t00; m[1] = t01; m[2] = t02; m[3] = t03;
	m[4] = t10; m[5] = t11; m[6] = t12; m[7] = t13;
	m[8] = t20; m[9] = t21; m[10] = t22; m[11] = t23;
	m[12] = t30; m[13] = t31; m[14] = t32; m[15] = t33;
}

// Matrix multiplication
Matrix Matrix::operator*(const Matrix& mat) const {
	float result[16];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result[i*4+j] = 0.0f;

			for (int k = 0; k < 4; k++) {
				result[i*4+j] += m[i*4+k]*mat.m[k*4+j];
			}
		}
	}
	return Matrix(result);
}

// Matrix determinant
float Matrix::Determinant() const {
	return (m[0] * m[5] - m[1] * m[4]) * (m[10] * m[15] - m[11] * m[14]) -
	       (m[0] * m[6] - m[2] * m[4]) * (m[9] * m[15] - m[11] * m[13]) +
	       (m[0] * m[7] - m[3] * m[4]) * (m[9] * m[14] - m[10] * m[13]) +
	       (m[1] * m[6] - m[2] * m[5]) * (m[8] * m[15] - m[11] * m[12]) -
	       (m[1] * m[7] - m[3] * m[5]) * (m[8] * m[14] - m[10] * m[12]) +
	       (m[2] * m[7] - m[3] * m[6]) * (m[8] * m[13] - m[9] * m[12]);
}

// Upper-left 3x3 submatrix determinant
float Matrix::Determinant3x3() const {
	return m[0] * (m[5] * m[10] - m[6] * m[9]) - 
	       m[1] * (m[4] * m[10] - m[6] * m[8]) +
	       m[2] * (m[4] * m[9]  - m[5] * m[8]);
}

// Matrix transpose
Matrix Matrix::Transpose() const {
	return Matrix(m[0], m[4], m[8],  m[12],
		      m[1], m[5], m[9],  m[13],
		      m[2], m[6], m[10], m[14],
		      m[3], m[7], m[11], m[15]);
}

// Matrix inverse
bool Matrix::Inverse(Matrix& out) const {
    	float d = Determinant();
    	if (d == 0.0f)
    		return false;

	// Cramer's rule (so help me, God)
	
    	d = 1.0f/d;
    
    	out.m[0] = d * (m[5] * (m[10] * m[15] - m[11] * m[14]) + m[6] * (m[11] * m[13] - m[9] * m[15]) + m[7] * (m[9] * m[14] - m[10] * m[13]));
    	out.m[1] = d * (m[9] * (m[2] * m[15] - m[3] * m[14]) + m[10] * (m[3] * m[13] - m[1] * m[15]) + m[11] * (m[1] * m[14] - m[2] * m[13]));
    	out.m[2] = d * (m[13] * (m[2] * m[7] - m[3] * m[6]) + m[14] * (m[3] * m[5] - m[1] * m[7]) + m[15] * (m[1] * m[6] - m[2] * m[5]));
    	out.m[3] = d * (m[1] * (m[7] * m[10] - m[6] * m[11]) + m[2] * (m[5] * m[11] - m[7] * m[9]) + m[3] * (m[6] * m[9] - m[5] * m[10]));
    	out.m[4] = d * (m[6] * (m[8] * m[15] - m[11] * m[12]) + m[7] * (m[10] * m[12] - m[8] * m[14]) + m[4] * (m[11] * m[14] - m[10] * m[15]));
    	out.m[5] = d * (m[10] * (m[0] * m[15] - m[3] * m[12]) + m[11] * (m[2] * m[12] - m[0] * m[14]) + m[8] * (m[3] * m[14] - m[2] * m[15]));
    	out.m[6] = d * (m[14] * (m[0] * m[7] - m[3] * m[4]) + m[15] * (m[2] * m[4] - m[0] * m[6]) + m[12] * (m[3] * m[6] - m[2] * m[7]));
    	out.m[7] = d * (m[2] * (m[7] * m[8] - m[4] * m[11]) + m[3] * (m[4] * m[10] - m[6] * m[8]) + m[0] * (m[6] * m[11] - m[7] * m[10]));
    	out.m[8] = d * (m[7] * (m[8] * m[13] - m[9] * m[12]) + m[4] * (m[9] * m[15] - m[11] * m[13]) + m[5] * (m[11] * m[12] - m[8] * m[15]));
    	out.m[9] = d * (m[11] * (m[0] * m[13] - m[1] * m[12]) + m[8] * (m[1] * m[15] - m[3] * m[13]) + m[9] * (m[3] * m[12] - m[0] * m[15]));
    	out.m[10] = d * (m[15] * (m[0] * m[5] - m[1] * m[4]) + m[12] * (m[1] * m[7] - m[3] * m[5]) + m[13] * (m[3] * m[4] - m[0] * m[7]));
    	out.m[11] = d * (m[3] * (m[5] * m[8] - m[4] * m[9]) + m[0] * (m[7] * m[9] - m[5] * m[11]) + m[1] * (m[4] * m[11] - m[7] * m[8]));
    	out.m[12] = d * (m[4] * (m[10] * m[13] - m[9] * m[14]) + m[5] * (m[8] * m[14] - m[10] * m[12]) + m[6] * (m[9] * m[12] - m[8] * m[13]));
    	out.m[13] = d * (m[8] * (m[2] * m[13] - m[1] * m[14]) + m[9] * (m[0] * m[14] - m[2] * m[12]) + m[10] * (m[1] * m[12] - m[0] * m[13]));
    	out.m[14] = d * (m[12] * (m[2] * m[5] - m[1] * m[6]) + m[13] * (m[0] * m[6] - m[2] * m[4]) + m[14] * (m[1] * m[4] - m[0] * m[5]));
    	out.m[15] = d * (m[0] * (m[5] * m[10] - m[6] * m[9]) + m[1] * (m[6] * m[8] - m[4] * m[10]) + m[2] * (m[4] * m[9] - m[5] * m[8]));
								        
	return true;
}

// Print Matrix
std::ostream& operator<<(std::ostream& out, const Matrix& mat) {
	return out << StringPrintf("[ %f, %f, %f, %f ]\n"       
				   "[ %f, %f, %f, %f ]\n"
				   "[ %f, %f, %f, %f ]\n"           
				   "[ %f, %f, %f, %f ]",  
				   mat.m[0], mat.m[1], mat.m[2], mat.m[3],
				   mat.m[4], mat.m[5], mat.m[6], mat.m[7],
				   mat.m[8], mat.m[9], mat.m[10], mat.m[11],  
				   mat.m[12], mat.m[13], mat.m[14], mat.m[15]);
}


}
