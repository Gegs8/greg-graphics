#include <string.h>
#include "file.h"
#include <stdlib.h>

int
parse_file(FILE *pt, matrix model, int **edges, size_t *num_edges, size_t *num_verts)
{
	char buffer[1024];
	fgets(buffer, sizeof(buffer), pt);
	fgets(buffer, sizeof(buffer), pt);

	int id, temporary, counter = 0;
	do
	{
		sscanf(buffer, "%d", &id);

		model[id] = (vector)malloc(3*sizeof(double));
		if(model[id] == NULL) return -1;

		sscanf(buffer, "%dx%lfy%lfz%lf\n", &temporary, &model[id][0], &model[id][1], &model[id][2]);
		fgets(buffer, sizeof(buffer), pt);
		++counter;
	}
	while(strcmp(buffer, "edges:\n")!=0);
	fgets(buffer, sizeof(buffer), pt);
	int from, to, nr = 0;
	do
	{
		sscanf(buffer, "%d>%d", &from, &to);

		edges[nr] = (int*)malloc(2*sizeof(int));
		if(edges[id] == NULL) return -1;

		edges[nr][0] = from;
		edges[nr][1] = to;
		++nr;
		fgets(buffer, sizeof(buffer), pt);
	}
	while(buffer[0]!=' ');
	*num_edges = nr;
	*num_verts = counter;
	return 0;
}
		



