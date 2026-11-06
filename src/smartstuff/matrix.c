#include "matrix.h"
#include "math.h"
#include <stdlib.h>
#include <stddef.h>

matrix
create_rotation_matrix(double angle, vector vec)
{
	double r, x, y, z;
	r = cosinus(angle/2);
	double scale = sinus(angle/2)/squareroot(vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2]);
	x = vec[0]*scale;
	y = vec[1]*scale;
	z = vec[2]*scale;
	matrix rotate;
       	rotate = (matrix)malloc(3*sizeof(vec));
	for(int i = 0; i < 3; ++i)rotate[i] = (vector)malloc(3*sizeof(*vec));
	rotate[0][0] = 1-2*(y*y+z*z);
	rotate[1][1] = 1-2*(x*x+z*z);
	rotate[2][2] = 1-2*(x*x+y*y);
	rotate[0][1] = 2*(x*y+r*z);
	rotate[0][2] = 2*(x*z-r*y);
	rotate[1][0] = 2*(x*y-r*z);
	rotate[1][2] = 2*(y*z+r*x);
	rotate[2][0] = 2*(x*z+r*y);
	rotate[2][1] = 2*(y*z-r*x);
	return rotate;
}

matrix
create_blank_matrix(size_t vec_num, size_t vec_size)
{
	matrix ptr = (matrix)malloc(vec_num * sizeof(double*));
	for(size_t i = 0; i < vec_num; ++i)
	{
		ptr[i] = (double*)malloc(vec_size * sizeof(double));
		for(size_t j = 0; j < vec_size; ++j)
			ptr[i][j] = 0;
	}
	return ptr;
	
}

matrix
scale_matrix(matrix model, size_t width, size_t height, double scale)
{
	
	for(size_t i = 0; i < width; ++i)
	{
		for(size_t j = 0; j < height; ++j)
		{
			model[i][j] = model[i][j] * scale;
		}
	}
	return model;
}

matrix
translate_matrix(matrix model, size_t model_vec_num, size_t model_vec_size, vector vec, size_t vec_size)
{
	if(model_vec_size != vec_size)
		return model; //Vector and Matrix have different lengths
	for(size_t i = 0; i < model_vec_num; ++i)
		for(size_t j = 0; j < vec_size; ++j)
			model[i][j] = model[i][j] + vec[j];
	return model;
}
matrix
multiply_matrixes(matrix model, size_t model_vec_num, size_t model_vec_size, matrix transform, size_t trans_vec_num, size_t trans_vec_size)
{
	if (model_vec_size != trans_vec_num) return model;
	matrix output = (matrix)malloc(model_vec_num*sizeof(vector));
	double sum;
	for (size_t vec_num = 0; vec_num < model_vec_num; ++vec_num)
	{
		output[vec_num] = (vector)malloc(trans_vec_size*sizeof(vector*));
		for(size_t vec_var = 0; vec_var < trans_vec_size; ++vec_var)
		{
			sum = 0;
			for (size_t i = 0; i < model_vec_size; ++i)
				sum += transform[i][vec_var]*model[vec_num][i];
			output[vec_num][vec_var] = sum;
		}
	}
	
	return output;
}

void free_matrix(matrix model, size_t x)
{
	for(size_t i = 0; i < x; ++i)
		free(model[i]);
	free(model);
}

