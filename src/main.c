#include <GL/glew.h>
#include <GL/glext.h>
#include <stdio.h>
#include <GLFW/glfw3.h>

#include "tri.frag.h"
#include "tri.vert.h"

#define WINDOW_TITLE "OPENGL TIME"

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


	float vertices[] = {
		-1.0,-1.0,+0.0,
		+1.0,-1.0,+0.0,
#include <GL/gl>
		+0.0,+1.0,+0.0,
	};
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	printf("%s", SHADER_TRI_VERT);
	while (!glfwWindowShouldClose(window)) {
		glClearColor(1.0, 1.0, 0.5,0.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
