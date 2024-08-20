#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include <glm/vec2.hpp>
#include <algorithm>
#include <math.h>
#include <stdexcept>
#include <vector>

#include"shaderClass.h"
#include "Platform.h"
#include "Piramide.h"

namespace Physics {
    //class PiramideAABB; // Forward declaration

    //class AABB {
    //public:
    //    glm::vec3 position;
    //    glm::vec3 scale;

    //    AABB(const glm::vec3& position, const glm::vec3& scale);
    //    bool intersects(const AABB& other) const;
    //    bool intersects(const PiramideAABB& other) const; // Ёто объ€вление должно быть здесь
    //};

    //class PiramideAABB {
    //public:
    //    glm::vec3 position;
    //    float radius;

    //    PiramideAABB(const glm::vec3& position, float radius);
    //};

    class Camera {
    public:
        glm::vec3 Position;
        glm::vec3 Velocity;
        glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -0.1f);
        glm::vec3 Up = glm::vec3(0.0f, 0.1f, 0.0f);
        glm::mat4 cameraMatrix = glm::mat4(1.0f);
        bool onGround = false;
        static constexpr float walkSpeed = 1.0f;
        static constexpr float rotationSpeed = 0.06f;
        static constexpr float jumpHeight = 3.0f;
        static constexpr float eyeHeight = 0.2f;

        bool firstClick = true;

        static constexpr float Gravity = 10.0f;
        int width;
        int height;
        float need = 40.0f;
        float need_speed = 4.0;
        float deltaTime = 0.1f;
        float speed = 0.1f;
        float sensitivity = 100.0f;
        float initialHeightOffset = 0.1f;
        float verticialVelocity = 0.0f;
        std::vector<Platform>platforms;
        std::vector<PiramideAABB>piramides;

        Camera(int width, int height, glm::vec3 position, glm::vec3 velocity);
        void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
        void updateDeltaTime(float deltaTime);
        glm::mat4 GetViewMatrix();
        void Matrix(Shader& shader, const char* uniform);
        void Inputs(GLFWwindow* window);
        bool collides(const Platform& platform) const;
        bool collides(const PiramideAABB& piramide) const;
        void addPlatform(const Platform& platform); // ћетод дл€ добавлени€ платформы
        void addPiramide(const PiramideAABB& piramide);
    };
}
#endif


