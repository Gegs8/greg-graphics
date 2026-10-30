#include <stdio.h>
#include <stdlib.h>

#include "graphics/fbdev.h"

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

	for(unsigned int r = 0; r < 256; ++r) {
		for(unsigned int g = 0; g < 256; ++g) {
			for(unsigned int b0 = 0; b0 < 4; ++b0) {
				for(unsigned int b1 = 0; b1 < 4; ++b1) {
					put_pix(&dpi, (r<<16)|(g<<8)|(b1*64+b0*16), r + 256*b0, g + 256*b1);
				}
			}
		}
	}
	flush_device(&dpi);

	char c;
	scanf("%c", &c);
	printf("char: %c\n", c);
	destroy_device();
}

