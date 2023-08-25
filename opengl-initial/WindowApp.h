#pragma once
#include "Shader.h"
#include <GLFW/glfw3.h>
#include <cstdlib>


class WindowApp
{
private:
	GLFWwindow* window;
    float vertices[18];
	Shader* shader;
    unsigned int indices[3];
	unsigned int EBO;
	GLuint VAO, VBO;
	void graphics_config();
	void shaders_config();

public:
	WindowApp();
	void run_loop();
};

