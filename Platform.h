#ifndef PLATFORM_CLASS_H
#define PLATFORM_CLASS_H

#include <glm/glm.hpp>

class Platform {
public:
    glm::vec3 position;
    glm::vec3 scale;

    Platform(const glm::vec3& position, const glm::vec3& scale)
        : position(position), scale(scale) {}

    bool collides(const glm::vec3& point) const {
        return point.x >= position.x && point.x <= position.x + scale.x &&
            point.y >= position.y && point.y <= position.y + scale.y &&
            point.z >= position.z && point.z <= position.z + scale.z;
    }
};

#endif // PLATFORM_CLASS_H
