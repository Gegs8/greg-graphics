#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include "graphics/render.h"
#include "graphics/fbdev.h"
#include "graphics/graphics.h"
#include "smartstuff/math.h"
#include "smartstuff/matrix.h"
#include "file.h"

int main(int argc, char **argv, char **envp) {
	(void)argc;
	(void)argv;

	char **p;

	for(p = envp; *p; ++p) {
		//puts(*p);
	}

	struct drawplane_info dpi;
	if(init_device(&dpi) < 0) {
		perror("init_device");
		exit(1);
	}
	
	FILE *pt = fopen("/home/gegs8/greg/models/cube", "r");
	matrix model = (matrix)malloc(1024*sizeof(vector));

	for(int i = 0; i < 1024; ++i)model[i] = (vector)malloc(3*sizeof(double));

	int **edges = (int**)malloc(1024*sizeof(int*));

	for(int i = 0; i < 1024; ++i) edges[i] = (int*)malloc(2*sizeof(int));

	size_t num_edges, num_verts;
	if(parse_file(pt, model, edges, &num_edges, &num_verts) < 0) {
		perror("parse_file");
		exit(1);
	}
	double translate[3] = {0, 0, 8};
	int zero = 0;
	for(unsigned int i = 0; ; ++i) {
		matrix m2 = multiply_matrixes(model, num_verts, 3, create_rotation_matrix(PI*i/128.0, (double[]){1.0, 0.0, 2.0}), 3, 3);
		m2 = translate_matrix(m2,  num_verts, 3, translate, 3);

		clear_dpi(&dpi, 0x000000);
		render_model(&dpi, m2, edges, num_edges, num_verts, 500);
		for(size_t j = 0; j < num_verts; ++j) free(m2[j]);
		free(m2);
		flush_device(&dpi);
		ioctl(give_fb(), FBIO_WAITFORVSYNC, &zero);
	}
	

	for(size_t i = 0; i < num_verts; ++i)
	{
		printf("Vertice %zu, x = %lf, y = %lf, z = %lf\n", i, model[i][0], model[i][1], model[i][2]);
	}

	vector axis = (vector)malloc(3*sizeof(*axis));
	axis[0]=7;
	axis[1]=3;
	axis[2]=1;
	matrix rotate = (matrix)malloc(3*sizeof(axis));
	rotate = create_rotation_matrix(PI, axis);
	matrix counter_rotate = create_blank_matrix(3, 3);
	counter_rotate = create_rotation_matrix(PI, axis);
	rotate = multiply_matrixes(rotate, 3, 3, counter_rotate, 3, 3);
	for(int a = 0; a < 3; ++a)
	{
		for(int b = 0; b < 3; ++b)
			printf("%.8f, ", rotate[a][b]);
		putchar('\n');
	}
	
	flush_device(&dpi);
	destroy_device();
}

