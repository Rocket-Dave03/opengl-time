#ifndef MODEL_H
#define MODEL_H
#include "cglm/types.h"

struct Model {
	char *filename;
	unsigned long vert_count;
	unsigned long tex_coord_count;
	unsigned long vert_normal_count;
	vec3 *verts;
	vec2 *vert_normal_coords;
	vec2 *tex_coords;
};

struct Model *model_load_from_file(char *filepath);
void model_free(struct Model *m);
#endif // MODEL_H
