#version 460 core
in vec2 TexCoords;
out vec4 FragColor;

uniform vec3 viewDir; // Направление взгляда камеры

// Нормализованный вектор света для солнца
vec3 lightDir = normalize(vec3(0.0, 0.5, 1.0)); // Направление солнца

void main()
{
    // Преобразование текстурных координат в диапазон [-1, 1]
    vec2 uv = TexCoords * 2.0 - 1.0;

    // Вектор направления от центра к фрагменту
    vec3 fragDir = normalize(vec3(uv, 1.0));

    // Проверка, находится ли солнце перед фрагментом и совпадает ли направление камеры с направлением света
    bool sunInFront = dot(lightDir, fragDir) > 0.0;
    bool cameraFacingSun = dot(lightDir, viewDir) > 0.0;

    // Цвета для солнца и неба
    vec3 sunColor = vec3(0.95, 0.9, 0.6); // Цвет для солнца
    float sunIntensity = pow(dot(lightDir, fragDir), 32.0); // Интенсивность солнца
    vec3 sun = sunColor * sunIntensity;

    vec3 topColor = vec3(0.529, 0.808, 0.922); // Голубой цвет для верха неба
    vec3 bottomColor = vec3(1.0, 1.0, 1.0);   // Белый цвет для низа неба
    vec3 skyColor = mix(bottomColor, topColor, TexCoords.y);

    if (sunInFront && cameraFacingSun) {
    // Ничего не делаем, чтобы солнце не отображалось
    }
    else {
        skyColor += sun;
    }

    FragColor = vec4(clamp(skyColor, 0.0, 1.0), 1.0);
}