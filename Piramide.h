    #ifndef PIRAMIDE_CLASS_H
    #define PIRAMIDE_CLASS_H

    #include <glm/glm.hpp>
    #include <algorithm>
    #include <iostream>

class PiramideAABB {
public:
    glm::vec3 position; // ÷ентр основани€ пирамиды
    glm::vec3 scale;    // –азмеры основани€ и высота пирамиды

    PiramideAABB(const glm::vec3& position, const glm::vec3& scale)
        : position(position), scale(scale) {}

    bool collides(const glm::vec3& point) const {
        // ѕроверка по высоте
        if (point.y < position.y || point.y > position.y + scale.y) {
            return false;
        }

        // ќпредел€ем максимальное горизонтальное рассто€ние на текущей высоте
        float heightRatio = (point.y - position.y) / scale.y;
        float maxHorizontalDistance = (1.0f - heightRatio) * (scale.x / 2.0f);

        // –асчет горизонтального рассто€ни€ от центра пирамиды
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

        // ¬ысота, на которой находитс€ точка
        float heightRatio = (point.y - position.y) / scale.y;

        // ћаксимальное горизонтальное рассто€ние на текущей высоте
        float maxHorizontalDistance = (1.0f - heightRatio) * (scale.x / 2.0f);

        // –асчет горизонтального рассто€ни€ от центра пирамиды
        float deltaX = point.x - position.x;
        float deltaZ = point.z - position.z;
        float horizontalDistance = glm::sqrt(deltaX * deltaX + deltaZ * deltaZ);

        if (horizontalDistance > maxHorizontalDistance) {
            // ≈сли точка выходит за границы пирамиды, перемещаем еЄ на границу
            float excessDistance = horizontalDistance - maxHorizontalDistance;
            glm::vec3 direction = glm::normalize(glm::vec3(deltaX, 0, deltaZ));
            newPosition -= direction * excessDistance;
        }

        //  орректировка по высоте: устанавливаем точку на поверхности пирамиды
        newPosition.y = position.y + heightRatio * scale.y;

        return newPosition;
    }
};
#endif
