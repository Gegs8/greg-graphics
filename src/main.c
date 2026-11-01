#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	
	parse_file(pt, model, edges);

	for(unsigned int r = 0; r < 256; ++r) {
		for(unsigned int g = 0; g < 256; ++g) {
			for(unsigned int b0 = 0; b0 < 4; ++b0) {
				for(unsigned int b1 = 0; b1 < 4; ++b1) {
					put_pix(&dpi, (r<<16)|(g<<8)|(b1*64+b0*16), r + 256*b0, g + 256*b1);
				}
			}
		}
	}
	for(int x = 1000; x<1900; ++x)
	{
		put_pix(&dpi, 0xff0000, x, -sinus(x/100.0)*100+512);
		put_pix(&dpi, 0x00ff00, x, -cosinus(x/100.0)*100+512);
		//printf("%d, %f\n", x, sinus(x/10.0));
	}
	vector axis = (vector)malloc(3*sizeof(*axis));
	axis[0]=0;
	axis[1]=1;
	axis[2]=2;
	matrix rotate = (matrix)malloc(3*sizeof(axis));
	rotate = create_rotation_matrix(PI/3, axis);
	for(int a = 0; a < 3; ++a)
	{
		for(int b = 0; b < 3; ++b)
			printf("%.8f, ", rotate[a][b]);
		putchar('\n');
	}
	
	dot(&dpi, 1000, 1000, 5);
	flush_device(&dpi);
	destroy_device();
}

