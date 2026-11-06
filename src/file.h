#ifndef FILE_H
#define FILE_H

#include "smartstuff/matrix.h"
#include <stdio.h>


int parse_file(FILE *pt, matrix model, int **edges, size_t *num_edges, size_t *num_verts);

#endif

