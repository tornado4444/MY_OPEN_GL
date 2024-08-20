#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 camMatrix;

void main()
{
    vec4 pos = model * vec4(aPos, 1.0f);
    gl_Position = camMatrix * pos;
}