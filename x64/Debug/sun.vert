#version 460 core
layout (location = 0) in vec3 aPos;
out vec2 TexCoords;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = aPos.xy + 0.5; // Преобразование координат в диапазон [0,1]
    // Позиция в пространстве видовой матрицы и проекции
    vec4 pos = projection * view *  vec4(aPos, 1.0);

    // Устанавливаем gl_Position
    gl_Position = pos;
}
