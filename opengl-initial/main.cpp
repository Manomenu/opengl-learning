#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>

#define ERR(source) (perror(source), fprintf(stdout, "%s:%d\n", __FILE__, __LINE__), glfwTerminate(), exit(EXIT_FAILURE))

void initialize_window();
void create_window(GLFWwindow** window);
void glad_init();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void window_config(GLFWwindow* window);
void run_loop(GLFWwindow* window);
void processInput(GLFWwindow* window);

int main(int argc, char** argv)
{
    GLFWwindow* window;

    (void)initialize_window();
    (void)create_window(&window);
    (void)glad_init();
    (void)window_config(window);
    (void)run_loop(window);

    return EXIT_SUCCESS;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void run_loop(GLFWwindow* window)
{
    while (!glfwWindowShouldClose(window))
    {
        //clean a frame
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //input
        processInput(window);

        //rendering commands here

        //check and call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}

void window_config(GLFWwindow* window)
{
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void initialize_window()
{
    if (glfwInit() == GLFW_FALSE)
        ERR("glfwInit");
    (void)glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    (void)glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    (void)glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void create_window(GLFWwindow** window)
{
    *window = glfwCreateWindow(800, 600, "Sztanga Window", NULL, NULL);
    if (!(*window))
        ERR("Failed to create GLFW window");
    glfwMakeContextCurrent(*window);
}

void glad_init()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        ERR("Failed to initialize GLAD");
}

/// <summary>
///     Gets called every time the window size is changed,
///     Remember: callback functions have to be defined after window creation 
///     and before render loop.
/// </summary>
/// <param name="window"></param>
/// <param name="width"></param>
/// <param name="height"></param>
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}