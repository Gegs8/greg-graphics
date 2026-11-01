#ifndef MATRIX_H
#define MATRIX_H
	
typedef double* vector;

typedef double** matrix;

matrix create_rotation_matrix(double angle, vector vec);

#endif
