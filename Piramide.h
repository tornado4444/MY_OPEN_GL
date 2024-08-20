    #ifndef PIRAMIDE_CLASS_H
    #define PIRAMIDE_CLASS_H

    #include <glm/glm.hpp>
    #include <algorithm>
    #include <iostream>

class PiramideAABB {
public:
    glm::vec3 position; // ����� ��������� ��������
    glm::vec3 scale;    // ������� ��������� � ������ ��������

    PiramideAABB(const glm::vec3& position, const glm::vec3& scale)
        : position(position), scale(scale) {}

    bool collides(const glm::vec3& point) const {
        // �������� �� ������
        if (point.y < position.y || point.y > position.y + scale.y) {
            return false;
        }

        // ���������� ������������ �������������� ���������� �� ������� ������
        float heightRatio = (point.y - position.y) / scale.y;
        float maxHorizontalDistance = (1.0f - heightRatio) * (scale.x / 2.0f);

        // ������ ��������������� ���������� �� ������ ��������
        float deltaX = point.x - position.x;
        float deltaZ = point.z - position.z;
        float horizontalDistance = glm::sqrt(deltaX * deltaX + deltaZ * deltaZ);

        bool collision = horizontalDistance <= maxHorizontalDistance;
        /*if (collision) {
            std::cout << "Collision detected at height ratio: " << heightRatio << " with max horizontal distance: " << maxHorizontalDistance << std::endl;
        }
        else {
            std::cout << "Horizontal distance check failed: " << horizontalDistance << " > " << maxHorizontalDistance << std::endl;
        }*/

        return collision;
    }

    glm::vec3 resolveCollision(const glm::vec3& point) const {
        glm::vec3 newPosition = point;

        // ������, �� ������� ��������� �����
        float heightRatio = (point.y - position.y) / scale.y;

        // ������������ �������������� ���������� �� ������� ������
        float maxHorizontalDistance = (1.0f - heightRatio) * (scale.x / 2.0f);

        // ������ ��������������� ���������� �� ������ ��������
        float deltaX = point.x - position.x;
        float deltaZ = point.z - position.z;
        float horizontalDistance = glm::sqrt(deltaX * deltaX + deltaZ * deltaZ);

        if (horizontalDistance > maxHorizontalDistance) {
            // ���� ����� ������� �� ������� ��������, ���������� � �� �������
            float excessDistance = horizontalDistance - maxHorizontalDistance;
            glm::vec3 direction = glm::normalize(glm::vec3(deltaX, 0, deltaZ));
            newPosition -= direction * excessDistance;
        }

        // ������������� �� ������: ������������� ����� �� ����������� ��������
        newPosition.y = position.y + heightRatio * scale.y;

        return newPosition;
    }
};
#endif
