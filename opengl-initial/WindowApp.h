#pragma once
#include "Shader.h"
#include "Camera.h"
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
	struct WindowData
	{
		GLFWwindow* window;
		int width, height;
	};

	float vertices[36 * 5];
	float deltaTime;
	float lastFrame;
	WindowData wd;
	GLuint VAO, VBO;
	TextureData textureData;
	TextureData textureDataContainer;
	Shader* shader;
	glm::vec3 cubePositions[10];
	void graphics_config();
	void shaders_config();
	void textureData_config();
	void processInput();
	void camera_config();

	static float lastX, lastY;
	static Camera* camera;
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

public:
	WindowApp();
	void run_loop();
};

