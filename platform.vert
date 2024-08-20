#version 460 core

// Позиция / Координаты
layout (location = 0) in vec3 aPos;
// Цвета
layout (location = 1) in vec3 aColor;
// Текстурные координаты
layout (location = 2) in vec2 aTex;
// Нормали(не обязательно нормализованные)
layout (location = 3) in vec3 aNormal;


// Выводит цвет для фрагментного шейдера
out vec3 color;
// Выводит координаты текстуры во фрагментный шейдер
out vec2 texCoord;
// Выводит нормали для фрагетного шейдера
out vec3 Normal;
// Выводит текущую позицию для фрагментного шейдера
out vec3 crntPos;

// Импортирует матрицу камеры из основной функции
uniform mat4 camMatrix;
// Импортирует матрицу модели из основной функции
uniform mat4 model;


void main()
{
	// вычисляет текущую позицию
	crntPos = vec3(model * vec4(aPos, 1.0f));
	// Выводит позиции/координаты всех вершин
	gl_Position = camMatrix * vec4(crntPos, 1.0);

	// Назначает цвета из данных вершин для "color"
	color = aColor;
	// Назначает координаты текстуры из данных вершин в "texCoord"
	texCoord = aTex;
	// Назначает нормаль из данных вершин на «Нормальный»
	Normal = aNormal;
}