#ifndef RENDER_H
#define RENDER_H

#include "../smartstuff/matrix.h"
#include "drawplane.h"
#include <stddef.h>

void clear_dpi(struct drawplane_info *dpi, uint32_t col);

void render_model(struct drawplane_info *dpi, matrix model, int **edges, size_t num_edges, size_t num_verts, double zoom);

void draw_line (struct drawplane_info *dpi, uint32_t col, vector point1, vector point2);

#endif
