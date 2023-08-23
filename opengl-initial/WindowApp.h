#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>

class WindowApp
{
private:
	GLFWwindow* window;
    float vertices[2][9];
	unsigned int shaderProgram[2];
    unsigned int indices[3];
	unsigned int EBO;
	GLuint VAO[2], VBO[2];
	void graphics_config();
	void shaders_config();

public:
	WindowApp();
	void run_loop();
};

