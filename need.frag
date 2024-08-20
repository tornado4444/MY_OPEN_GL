#version 330 core
in vec2 TexCoords;
out vec4 FragColor;

// ����� ��� ����
vec3 topColor = vec3(0.529, 0.808, 0.922); // ������� ���� ��� ����� ����
vec3 bottomColor = vec3(1.0, 1.0, 1.0);   // ����� ���� ��� ���� ����

void main()
{
    vec2 uv = TexCoords * 2.0 - 1.0;
    // ���������� ������ � ����������� �� ���������� ��������� �� ��� Y
    vec3 skyColor = mix(bottomColor, topColor, TexCoords.y);

    FragColor = vec4(clamp(skyColor, 0.0, 1.0), 1.0);
}