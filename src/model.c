#include "model.h"

#include <cglm/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void parse_vec3(char *line, vec3 *out) {
	sscanf(line, " %f %f %f\n", (float *)out + 0, (float *)out + 1, (float *)out + 2);
}

void parse_vec2(char *line, vec2 *out) {
	sscanf(line, " %f %f\n", (float *)out + 0, (float *)out + 1);
}

unsigned int find_end_of_line(char *str) {
	// TODO
}

struct Model *model_load_from_file(char *filepath) {
	FILE *f = fopen(filepath, "r");
	if (f == NULL) {
		fprintf(stderr, "Failed to open file '%s': %s", filepath, strerror(errno));
		return NULL;
	}

	struct Model *model = malloc(sizeof(struct Model));
	if (model == NULL) {
		fprintf(stderr, "Failed to allocate memory: %s", strerror(errno));
		goto exit_file_close;
	}
	memset(model, 0, sizeof(struct Model));

	// Copy filapath into model
	unsigned long filepath_len = strlen(filepath) + 1;
	model->filename = malloc(filepath_len);
	if (model->filename == NULL) {
		fprintf(stderr, "Failed to allocate memory: %s", strerror(errno));
		goto exit_model_free;
	}
	memcpy(model->filename, filepath, filepath_len);


	{
		const int buf_size = 1024;
		char buff[buf_size];
		memset(buff, 0,  buf_size);
		unsigned int start_idx = 0;
		unsigned int read_idx = 0;
		while (!feof(f)) {
			int c = fread(buff+start_idx, 1, buf_size - 1 - start_idx, f);
			read_idx = 0;
			int e = ferror(f);
			if (e) {
				fprintf(stderr, "Error, unable to read from file: %d", e);
				goto exit_model_free;
			}
			buff[c] = 0; // NULL Terminator
			//
		}
	}

exit_model_free:
	model_free(model);
exit_file_close:
	fclose(f);
	return NULL;
}


void model_free(struct Model *m) {
	if (m == NULL) return;
	free(m->filename);
	free(m->verts);
	free(m->vert_normal_coords);
	free(m->tex_coords);

	m->filename = NULL;
	m->verts = NULL;
	m->vert_normal_coords = NULL;
	m->tex_coords = NULL;

	free(m);
}
