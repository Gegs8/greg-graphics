#include "matrix.h"
#include "math.h"
#include <stdlib.h>

matrix
create_rotation_matrix(double angle, vector vec)
{
	/*if(sizeof(vec)/sizeof(*vec)!=3)
		return -1;*/
	double r, x, y, z;
	r = cosinus(angle);
	double scale = sinus(angle)/squareroot(vec[0]*vec[0]+vec[1]*vec[1]+vec[2]+vec[2]);
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




