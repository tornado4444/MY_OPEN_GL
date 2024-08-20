#version 460 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 Normal;
in vec3 crntPos;

uniform sampler2D tex0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
    // окружающее освещение
    float ambient = 0.60f;

    // рассеянное освещение
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - crntPos);
    float diffuse = max(dot(normal, lightDirection), 0.0f);

    // зеркальное освещение
    float specularLight = 1.50f;
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
    float specular = specAmount * specularLight;

    // выводит окончательный цвет
    vec4 textureColor = texture(tex0, texCoord);
    vec4 lighting = vec4((diffuse + ambient + specular) * lightColor.rgb, 1.0f);
    FragColor = textureColor * lighting;
}