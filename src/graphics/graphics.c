#include "graphics.h"
#include "fbdev.h"

void
dot(struct drawplane_info *dpi, uint32_t col, unsigned int x, unsigned int y, unsigned int radius)
{
	unsigned int width = dpi->width;
	for(unsigned int i = x-radius; i <= x+radius; ++i) {
		if(i>=width)break;
			for(unsigned int j = y-radius; j <= y+radius; ++j) {
			if((x-i)*(x-i) + (y-j)*(y-j) <= radius*radius) {
				put_pix(dpi, col, i, j);
			}
		}
	}
}	
