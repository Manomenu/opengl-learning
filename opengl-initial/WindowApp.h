#pragma once
#include "Shader.h"
#include <GLFW/glfw3.h>
#include <cstdlib>


class WindowApp
{
private:
	struct TextureData
	{
		int width, height, nrChannels;
		unsigned char* data;
	};
	GLFWwindow* window;
    float vertices[18];
	Shader* shader;
    unsigned int indices[3];
	unsigned int EBO;
	GLuint VAO, VBO;
	TextureData textureData;
	void graphics_config();
	void shaders_config();
	void textureData_config();

public:
	WindowApp();
	void run_loop();
};

