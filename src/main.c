#include <cglm/cglm.h>
#include <cglm/types.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "tri.frag.h"
#include "tri.vert.h"

#include "model.h"

#define WINDOW_TITLE "OPENGL TIME"


void check_shader_error(GLuint shader) {
	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if(!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		fprintf(stderr, "Shader compilation error: %s", infoLog);
	}
}

void chech_program_error(GLuint prog) {
	int  success;
	char infoLog[512];
	glGetProgramiv(prog, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(prog, 512, NULL, infoLog);
		fprintf(stderr, "Shader program error: %s", infoLog);
	}
}

GLuint compile_shader_program(const char *vert_src, const char *frag_src) {
	GLuint vert = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert, 1, &vert_src,NULL);
	glCompileShader(vert);

	check_shader_error(vert);

	GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag, 1, &frag_src, NULL);
	glCompileShader(frag);

	check_shader_error(frag);

	GLuint program = glCreateProgram();
	glAttachShader(program, vert);
	glAttachShader(program, frag);
	glLinkProgram(program);

	chech_program_error(program);

	return program;
}

int main(void) {
	if (!glfwInit()) {
		fprintf(stderr, "Unable to init glfw");
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(1920/2, 1080/2, WINDOW_TITLE, NULL, NULL);
	if (!window) {
		fprintf(stderr, "Unable to create window");
		return -1;
	}
	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	if (!GLEW_VERSION_4_1) {
		fprintf(stderr,"Opengl 4.1 not suooported");
	}

	GLuint shader = compile_shader_program(SHADER_TRI_VERT, SHADER_TRI_FRAG);

	struct Model *m = model_load_from_file("./models/v1.obj");

	// model_free(m);

	float *vertices = (float *)m->verts;	

	// float vertices[] = {
	// 	-1.0,-1.0,+0.0,
	// 	+1.0,-1.0,+0.0,
	// 	+0.0,+1.0,+0.0,
	// };

	GLuint vao; 
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * m->vert_count, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glUseProgram(shader);




	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glClearColor(1.0, 1.0, 0.5,0.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, m->vert_count);

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
