#include "render.h"
#include "graphics.h"

#define ABS(X) (((X) > 0) ? (X) : (-(X)))

void
clear_dpi(struct drawplane_info *dpi, uint32_t col) {
	//for(unsigned int i = 0; i < dpi->height; ++i) {
			put_row(dpi, col, 0, 0, dpi->pitch*dpi->height*4);
	//}
}

void
render_model(struct drawplane_info *dpi, matrix model, int **edges, size_t num_edges, size_t num_verts,  double zoom)
{
	matrix projected = create_blank_matrix(num_verts, 2);
	for (size_t i = 0; i < num_verts; ++i)
	{
		projected[i][0] = model[i][0]/model[i][2];
		projected[i][1] = model[i][1]/model[i][2];
	}
	projected = scale_matrix(projected, num_verts, 2, zoom);
	double middle[2] = {dpi->width/2, dpi->height/2};
	projected = translate_matrix(projected, num_verts, 2, middle, 2);
	for (size_t i = 0; i < num_verts; ++i)
		dot(dpi, 0x40ff10, projected[i][0], projected[i][1], 100/model[i][2]);

	for (size_t i = 0; i < num_edges; ++i)
		draw_line(dpi, 0x00ff00, projected[edges[i][0]], projected[edges[i][1]]);
}

void
draw_line (struct drawplane_info *dpi, uint32_t col, vector point1, vector point2)
{
	int x1 = point1[0], y1 = point1[1], x2 = point2[0], y2 = point2[1];
	int dx = ABS(x2 - x1);
	int dy = -ABS(y2 - y1);
	int sx = x1 < x2 ? 1 : -1;
	int sy = y1 < y2 ? 1 : -1;
	int e = dx + dy;
	int e2, drawn = 0;
	unsigned int width = dpi->width, height = dpi->height;
	while(1) {
		if(ABS(x1) >= width || ABS(y1) >= height) break; 
		put_pix(dpi, col, x1, y1);
		e2 = 2 * e;
		if(e2 >= dy) {
			if(x1 == x2)
			{
				drawn = 1;
				break;
			}
			e += dy;
			x1 += sx;
		}
		if(e2 <= dx) {
			if(y1 == y2)
			{
				drawn = 1;
				break;
			}
			e += dx;
			y1 += sy;
		}
	}
	dx = dx;
	dy = dy;
	sx = x1 < x2 ? -1 : 1;
	sy = y1 < y2 ? -1 : 1;
	e = dx + dy;

	while(!drawn) {
		//if(ABS(x2) >= width || ABS(y2) >= height) break; 
		put_pix(dpi, col, x2, y2);
		e2 = 2 * e;
		if(e2 >= dy) {
			if(x1 == x2) break;
			e += dy;
			x2 += sx;
		}
		if(e2 <= dx) {
			if(y1 == y2) break;
			e += dx;
			y2 += sy;
		}
	}
	
}

