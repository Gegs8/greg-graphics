#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

	int **edges = (int**)malloc(1024*sizeof(int*));

	size_t num_edges, num_verts;
	if(parse_file(pt, model, edges, &num_edges, &num_verts) < 0) {
		perror("parse_file");
		exit(1);
	}
	double translate[3] = {-4, -4, 8};
	for(unsigned int i=0; i < 500; ++i) {
		matrix rotor = create_rotation_matrix(PI*i/128.0, (double[]){sinus(i/200.0),cosinus(i/400.0), 1.0});
		matrix m2 = multiply_matrixes(model, num_verts, 3, rotor, 3, 3);
		m2 = translate_matrix(m2,  num_verts, 3, translate, 3);
		clear_dpi(&dpi, 0x000000);
		render_model(&dpi, m2, edges, num_edges, num_verts, 500);
		for(size_t j = 0; j < num_verts; ++j) free(m2[j]);
		free(m2);
		for(size_t j = 0; j < 3; ++j) free(rotor[j]);
		free(rotor);
		flush_device(&dpi);
	}

	destroy_device();
	for (size_t i = 0; i < num_verts; ++i)
		free(model[i]);
	for (size_t i = 0; i < num_edges; ++i)
		free(edges[i]);
	free(model);
	free(edges);


}

