#include "graphics.h"
#include "fbdev.h"

inline void
dot(struct drawplane_info *dpi, unsigned int x, unsigned int y, unsigned int radius)
{
	for(unsigned int i = 1; i < (radius<<1); ++i)
		for(unsigned int j = 0; j<(radius+i%2-1); ++j)
			put_pix(dpi, 0xffffff, x-(i+1)/2+j, y-radius+(i+2)/2+j);
}	
