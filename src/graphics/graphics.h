#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "fbdev.h"

void dot(struct drawplane_info *dpi, uint32_t col, int x, int y, int radius);

#endif
