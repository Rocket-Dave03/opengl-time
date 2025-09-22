#include "model.h"

#include <cglm/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>




void parse_vec3(char *line, vec3 *out) {
	sscanf(line, " %f %f %f\n", (float *)out + 0, (float *)out + 1, (float *)out + 2);
}

void parse_vec2(char *line, vec2 *out) {
	sscanf(line, " %f %f\n", (float *)out + 0, (float *)out + 1);
}

void parse_line(struct Model *m, char *line, unsigned long len) {
	printf("parsing line: '%*s'", (int)len, line);
}

long find_end_of_line(char *str, unsigned long max_len) {
	unsigned long idx = 0;
	while (str[idx] != '\n') {idx++;};
	if (idx == max_len-1 || idx >= max_len - 1) {return -1;};
	// printf("line len = %lu\t", idx);
	return idx;
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
		const int buf_size = 1023;
		char buff[buf_size+1];
		memset(buff, 0,  buf_size+1);
		unsigned long start_idx = 0;
		bool reading = true;
		while (reading) {
			int c = fread(buff+start_idx, 1, buf_size - start_idx, f);
			bool last = feof(f);
			int e = ferror(f);
			c += start_idx;
			start_idx = 0;
			if (e) {
				fprintf(stderr, "Error, unable to read from file: %d", e);
				goto exit_model_free;
			}
			buff[c] = 0; // NULL Terminator
			// printf("%*s", c, buff);
			for(int o = 0; o < c && reading; o += find_end_of_line(buff+o, c-o)+1) {
				long len = find_end_of_line(buff+o, c-o);
				if (len == -1) {
					len = c - o - 1;

					start_idx = buf_size-o;
					// printf("Moving %4ld bytes '%.*s' to start\n", start_idx, (int)start_idx, buff+o);
					memmove(buff, buff + o, start_idx);
					if (last) {
						reading = false;
						goto proc_line;
					}
					break;
				};
			proc_line:
				printf("%.*s\n", (int)len, buff+o);
			}
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
