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
		unsigned int texture;
	};
	GLFWwindow* window;
    float vertices[32];
	Shader* shader;
    unsigned int indices[6];
	unsigned int EBO;
	GLuint VAO, VBO;
	TextureData textureData;
	TextureData textureDataContainer;
	void graphics_config();
	void shaders_config();
	void textureData_config();

public:
	WindowApp();
	void run_loop();
};

