#ifndef FBDEV_H
#define FBDEV_H

#include "drawplane.h"

int init_device(struct drawplane_info *dpi);
void destroy_device();
int give_fb();
int flush_device(struct drawplane_info *dpi);

#endif

