#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>

class WindowApp
{
private:
	GLFWwindow* window;
    float vertices[18];
	unsigned int shaderProgram;
    unsigned int indices[3];
	unsigned int EBO;
	GLuint VAO, VBO;
	void graphics_config();
	void shaders_config();

public:
	WindowApp();
	void run_loop();
};

