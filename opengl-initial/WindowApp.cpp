#include "WindowApp.h"

#define ERR(source) (perror(source), fprintf(stdout, "%s:%d\n", __FILE__, __LINE__), glfwTerminate(), exit(EXIT_FAILURE))

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void WindowApp::graphics_config()
{
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    glGenBuffers(1, &EBO);

    for (int i = 0; i < 2; i++)
    {
        glBindVertexArray(VAO[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[i]), vertices[i], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void WindowApp::shaders_config()
{
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "out vec4 vertexColor;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "   vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
        "}\0";

    const char* fragmentShaderSource[2] = {
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec4 vertexColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vertexColor;\n"
        "}\0"
        ,
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec4 myColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = myColor;\n"
        "}\0"
    };

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader[2];
    for (int i = 0; i < 2; i++)
    {
        fragmentShader[i] = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader[i], 1, &fragmentShaderSource[i], NULL);
        glCompileShader(fragmentShader[i]);
        glGetShaderiv(fragmentShader[i], GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader[i], 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        shaderProgram[i] = glCreateProgram();
        glAttachShader(shaderProgram[i], vertexShader);
        glAttachShader(shaderProgram[i], fragmentShader[i]);
        glLinkProgram(shaderProgram[i]);
        glGetProgramiv(shaderProgram[i], GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shaderProgram[i], 512, NULL, infoLog);
            std::cout << "ERROR::PROGRAM::VERTEX:COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        glDeleteShader(fragmentShader[i]);
    }
    glDeleteShader(vertexShader);
}

WindowApp::WindowApp() : 
    //vertices 
    //{
    //    0.5f,  0.5f, 0.0f,  // top right
    //    0.5f, -0.5f, 0.0f,  // bottom right
    //    -0.5f, -0.5f, 0.0f,  // bottom left
    //    -0.5f,  0.5f, 0.0f   // top left 
    //},
    //indices { 0, 1, 3, 1, 2, 3 }
    vertices 
    {
        {
            0.5f,  0.4f, 0.0f,  // top right
            0.5f, -0.6f, 0.0f,  // bottom right
            -0.5f, -0.6f, 0.0f  // bottom left
        },
        {
            -0.5f,  0.6f, 0.0f,   // top left 
            -0.5f, -0.4f, 0.0f,  // bottom left
            0.5f,  0.6f, 0.0f
        }
    },
    indices { 0, 1, 2 }
{

    if (glfwInit() == GLFW_FALSE)
        ERR("glfwInit");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "Sztanga Window", NULL, NULL);
    if (!window)
        ERR("Failed to create GLFW window");
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        ERR("Failed to initialize GLAD");

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    shaders_config();

    graphics_config();
}

void WindowApp::run_loop()
{
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        for (int i = 0; i < 2; i++)
        {
            glUseProgram(shaderProgram[i]);

            // update the uniform color
            if (i == 1)
            {
                float timeValue = glfwGetTime();
                float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
                int vertexColorLocation = glGetUniformLocation(shaderProgram[i], "myColor");
                glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
            }

            glBindVertexArray(VAO[i]);
            //glDrawArrays(GL_TRIANGLES, 0, 6);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glDeleteBuffers(1, &EBO);
    for (int i = 0; i < 2; i++)
        glDeleteProgram(shaderProgram[i]);
    glfwTerminate();
}

