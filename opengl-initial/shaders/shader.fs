#version 330 core
out vec4 FragColor;
// in vec3 vertexColor;
in vec3 posVec;
void main()
{
    FragColor = vec4(posVec, 1.0);
};