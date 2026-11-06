#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>
typedef double* vector;

typedef double** matrix;

matrix create_rotation_matrix(double angle, vector vec);

matrix scale_matrix(matrix model, size_t width, size_t height, double scale);

matrix multiply_matrixes(matrix model, size_t model_vec_num, size_t model_vec_size, matrix transform, size_t trans_vec_num, size_t trans_vec_size);

matrix translate_matrix(matrix model, size_t model_vec_num, size_t model_vec_size, vector vec, size_t vec_size);

matrix create_blank_matrix(size_t model_vec_num, size_t model_vec_size);

void wipe_matrix(matrix garbage, size_t x);

#endif
