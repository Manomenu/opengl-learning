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
    float vertices[36 * 5];
	Shader* shader;
	GLuint VAO, VBO;
	TextureData textureData;
	TextureData textureDataContainer;
	glm::vec3 cubePositions[10];
	void graphics_config();
	void shaders_config();
	void textureData_config();

public:
	WindowApp();
	void run_loop();
};

