#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 posVec;

uniform sampler2D myTexture;

void main()
{
    FragColor = texture(myTexture, TexCoord) + vec4(posVec, 1.0);
};