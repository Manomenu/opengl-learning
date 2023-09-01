#include "WindowApp.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define ERR(source) (perror(source), fprintf(stdout, "%s:%d\n", __FILE__, __LINE__), glfwTerminate(), exit(EXIT_FAILURE))

const int WIDTH = 800;
const int HEIGHT = 600;
const int VERSION_MAJOR = 3;
const int VERSION_MINOR = 3;
const glm::vec4 BACKGROUNDCOLOR = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f);

float WindowApp::lastX = WIDTH / 2.0f;
float WindowApp::lastY = HEIGHT / 2.0f;
Camera* WindowApp::camera = new Camera();

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void WindowApp::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (camera->firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        camera->firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
    lastX = xpos;
    lastY = ypos;
    camera->ProcessMouseMovement(xoffset, yoffset);
}

void WindowApp::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera->ProcessMouseScroll(yoffset);
}

WindowApp::WindowApp() :
    vertices
{
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
},
cubePositions
{
    glm::vec3(0.0f,  0.0f,  -20.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
},
lastFrame{ 0.0f },
deltaTime{ 0.0f }
{
    if (glfwInit() == GLFW_FALSE)
        ERR("glfwInit");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    wd.height = HEIGHT;
    wd.width = WIDTH;
    wd.window = glfwCreateWindow(wd.width, wd.height, "Sztanga Window", NULL, NULL);

    if (!wd.window)
        ERR("Failed to create GLFW window");
    glfwMakeContextCurrent(wd.window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        ERR("Failed to initialize GLAD");

    glfwSetFramebufferSizeCallback(wd.window, framebuffer_size_callback);

    shaders_config();
    graphics_config();
    textureData_config();
    camera_config();
}

void WindowApp::processInput()
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if (glfwGetKey(wd.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(wd.window, true);
    if (glfwGetKey(wd.window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
    if (glfwGetKey(wd.window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
    if (glfwGetKey(wd.window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
    if (glfwGetKey(wd.window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
}

void WindowApp::textureData_config()
{
    TextureData& td = textureData;
    glGenTextures(1, &td.texture);
    glBindTexture(GL_TEXTURE_2D, td.texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    
    
    stbi_set_flip_vertically_on_load(true);
    td.data = stbi_load("./images/crafting-table.png", &td.width, &td.height, &td.nrChannels, 0);
    if (td.data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, td.width, td.height, 0, GL_RGB,
            GL_UNSIGNED_BYTE, td.data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
        std::cout << "Failed to load texture" << std::endl;
    stbi_image_free(td.data);
    stbi_set_flip_vertically_on_load(false);

    TextureData& c = textureDataContainer;
    glGenTextures(1, &c.texture);
    glBindTexture(GL_TEXTURE_2D, c.texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    c.data = stbi_load("./images/container.jpg", &c.width, &c.height, &c.nrChannels, 0);
    if (c.data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, c.width, c.height, 0, GL_RGB,
            GL_UNSIGNED_BYTE, c.data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
        std::cout << "Failed to load texture" << std::endl;
    stbi_image_free(c.data);
}

void WindowApp::graphics_config()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void WindowApp::shaders_config()
{
    shader = new Shader("./shaders/shader.vs", "./shaders/shader.fs");
}

void WindowApp::camera_config()
{
    glfwSetInputMode(wd.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(wd.window, mouse_callback);
    glfwSetScrollCallback(wd.window, scroll_callback);
}

void WindowApp::run_loop()
{
    shader->use();
    shader->setInt("texture1", 0);
    shader->setInt("texture2", 1);
    

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(wd.window))
    {
        // input
        // -----
        processInput();

        // render
        // ------
        glClearColor(
            BACKGROUNDCOLOR.x, 
            BACKGROUNDCOLOR.y, 
            BACKGROUNDCOLOR.y, 
            BACKGROUNDCOLOR.z
        );
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureData.texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureDataContainer.texture);
        
        shader->setMat4("view", camera->GetViewMatrix());

        glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), wd.width / (float)wd.height, 0.1f, 100.0f);
        shader->setMat4("projection", projection);

        glBindVertexArray(VAO);
        for (int i = 0; i < sizeof(cubePositions) / sizeof(glm::vec3); i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            if (i % 3 == 0)
                model = glm::rotate(model, (float)glfwGetTime() * (i + 1) * glm::radians(20.1f), glm::vec3(0.5f, 1.0f, 0.0f));
            shader->setMat4("model", model);
            
            glDrawArrays(GL_TRIANGLES, 0, 36); // for drawing without EBO
            //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        glBindVertexArray(0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(wd.window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    delete shader;
    glfwTerminate();
}

