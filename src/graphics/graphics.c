#include "graphics.h"
#include "fbdev.h"

void
dot(struct drawplane_info *dpi, uint32_t col, int x, int y, int radius)
{
	int width = dpi->width;
	int height = dpi->height;
	for(int i = x-radius; i <= x+radius; ++i) {
		if(i>=width)break;
		if(i<0)continue;
			for(int j = y-radius; j <= y+radius; ++j) {
			if(j>=height)break;
			if(j<0)continue;
			if((x-i)*(x-i) + (y-j)*(y-j) <= radius*radius) {
				put_pix(dpi, col, i, j);
			}
		}
	}
}	
