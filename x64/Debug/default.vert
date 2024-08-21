#version 460 core

// Позиция/Координаты
layout (location = 0) in vec3 aPos;
// Цвета
layout (location = 1) in vec3 aColor;
// Текстурные координаты
layout (location = 2) in vec2 aTex;
// Нормали (не обязательно нормализованные)
layout (location = 3) in vec3 aNormal;

// Выводит цвет для фрагментного шейдера
out vec3 color;
out vec2 texCoord;
out vec3 Normal;
out vec3 crntPos;

// Импортирует матрицу камеры из основной функции
uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
    vec4 pos = model * vec4(aPos, 1.0f);
    crntPos = vec3(model * vec4(aPos, 1.0f));
    gl_Position = camMatrix * vec4(crntPos, 1.0);

    color = aColor;
    texCoord = aTex;
    Normal = mat3(transpose(inverse(model))) * aNormal;
}