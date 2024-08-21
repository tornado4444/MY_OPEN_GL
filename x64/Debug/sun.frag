#version 460 core
in vec2 TexCoords;
out vec4 FragColor;

uniform vec3 viewDir; // ����������� ������� ������

// ��������������� ������ ����� ��� ������
vec3 lightDir = normalize(vec3(0.0, 0.5, 1.0)); // ����������� ������

void main()
{
    // �������������� ���������� ��������� � �������� [-1, 1]
    vec2 uv = TexCoords * 2.0 - 1.0;

    // ������ ����������� �� ������ � ���������
    vec3 fragDir = normalize(vec3(uv, 1.0));

    // ��������, ��������� �� ������ ����� ���������� � ��������� �� ����������� ������ � ������������ �����
    bool sunInFront = dot(lightDir, fragDir) > 0.0;
    bool cameraFacingSun = dot(lightDir, viewDir) > 0.0;

    // ����� ��� ������ � ����
    vec3 sunColor = vec3(0.95, 0.9, 0.6); // ���� ��� ������
    float sunIntensity = pow(dot(lightDir, fragDir), 32.0); // ������������� ������
    vec3 sun = sunColor * sunIntensity;

    vec3 topColor = vec3(0.529, 0.808, 0.922); // ������� ���� ��� ����� ����
    vec3 bottomColor = vec3(1.0, 1.0, 1.0);   // ����� ���� ��� ���� ����
    vec3 skyColor = mix(bottomColor, topColor, TexCoords.y);

    if (sunInFront && cameraFacingSun) {
    // ������ �� ������, ����� ������ �� ������������
    }
    else {
        skyColor += sun;
    }

    FragColor = vec4(clamp(skyColor, 0.0, 1.0), 1.0);
}