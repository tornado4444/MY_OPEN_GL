#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>

namespace Physics {
	// ����������� ������
	Camera::Camera(int width, int height, glm::vec3 position, glm::vec3 velocity)
	{
		if (width == 0 || height == 0)
		{
			throw std::runtime_error("Width and height must be non-zero.");
		}
		Camera::width = width;
		Camera::height = height;
		Velocity = velocity + glm::vec3(0.0f, initialHeightOffset, 0.0f);
		Position = position + glm::vec3(0.0f, initialHeightOffset, 0.0f);
	}

	// ���������� ������ �������
	void Camera::updateDeltaTime(float deltaTime)
	{
		this->deltaTime = deltaTime;
	}

	// ���������� ������� ������
	void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
	{
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		view = glm::lookAt(Position, Position + Orientation, Up);
		if (height == 0) // ��������, ����� �������� ������� �� ����
		{
			throw std::runtime_error("�� ������ ��������� ����.");
		}

		float aspect = static_cast<float>(width) / height;
		if (aspect <= std::numeric_limits<float>::epsilon()) {
			std::cerr << "������: ������ ��� ������ ���� ����� ���� ��� ������� ����!" << std::endl;
			aspect = 1.0f; // ���������� �������� �� ���������
		}
		projection = glm::perspective(glm::radians(FOVdeg), aspect, nearPlane, farPlane);

		cameraMatrix = projection * view;
	}

	// ������� ������� ������
	void Camera::Matrix(Shader& shader, const char* uniform)
	{
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
	}

	// ��������� ������� ����
	glm::mat4 Camera::GetViewMatrix()
	{
		return glm::lookAt(Position, Position + Orientation, Up);
	}

	// �������� �������� � ����������
	bool Camera::collides(const Platform& platform) const {
		glm::vec3 footPosition = Position + glm::vec3(5.0f, -eyeHeight, 5.0f);
		return platform.collides(footPosition);
	}


	// �������� �������� � ���������
	bool Camera::collides(const PiramideAABB& piramide) const {
		bool collision = piramide.collides(Position);
		if (collision) {
			std::cout << "Collision with pyramid at: " << piramide.position.x << ", " << piramide.position.y << ", " << piramide.position.z << std::endl;
			std::cout << "Camera Position: " << Position.x << ", " << Position.y << ", " << Position.z << std::endl;
		}
		return collision;
	}

	// ���������� ���������
	void Camera::addPlatform(const Platform& platform) {
		platforms.push_back(platform);
	}

	// ���������� ��������
	void Camera::addPiramide(const PiramideAABB& piramide) {
		piramides.push_back(piramide);
	}



	// ��������� �����
	void Camera::Inputs(GLFWwindow* window)
	{
		glm::vec3 originalPosition = Position;

		Velocity.x = 0.0f;
		Velocity.z = 0.0f;

		// ������������ ���� ������
		if (glfwGetKey(window, GLFW_KEY_W))
		{
			Position += speed * glm::vec3(Orientation.x, 0.0f, Orientation.z) * need_speed;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			Position += speed * deltaTime * need * -glm::normalize(glm::cross(glm::vec3(Orientation.x, 0.0f, Orientation.z), Up));
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			Position += speed * glm::vec3(-Orientation.x, 0.0f, -Orientation.z) * need_speed;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			Position += speed * deltaTime * need * glm::normalize(glm::cross(glm::vec3(Orientation.x, 0.0f, Orientation.z), Up));
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			if (onGround)
			{
				Velocity.y = jumpHeight;  // ������
				onGround = false;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			Position += speed * -Up;  // ���������� ��� �����
		}
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		// ������������ ���� ����
		/*if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			if (firstClick)
			{
				glfwSetCursorPos(window, (width / 2), (height / 2));
				firstClick = false;
			}

			double mouseX, mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);

			float rotX = sensitivity * static_cast<float>(mouseY - (height / 2)) / height;
			float rotY = sensitivity * static_cast<float>(mouseX - (width / 2)) / width;

			glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

			if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
			{
				Orientation = newOrientation;
			}

			Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

			glfwSetCursorPos(window, (width / 2), (height / 2));
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			firstClick = true;
		}*/

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			if (firstClick)
			{
				glfwSetCursorPos(window, (width / 2), (height / 2));
				firstClick = false;
			}

			double mouseX;
			double mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);

			float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
			float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

			glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

			if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
			{
				Orientation = newOrientation;
			}

			Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
			glfwSetCursorPos(window, (width / 2), (height / 2));
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			firstClick = true;
		}

		// ���������� ����������
		if (!onGround)
		{
			Velocity.y -= Gravity * deltaTime;  // ���������� ��������� ������ � �������
		}
		// ���������� ������� �� Y
		Position.y += Velocity.y * deltaTime;
		onGround = false;
		for (const auto& platform : platforms) {
			if (collides(platform)) {
				onGround = true;
				Position.y = platform.position.y + platform.scale.y + eyeHeight;
				Velocity.y = 0.0f;
				break;
			}
		}

		// ���������� ������� �� X
		Position.x += Velocity.x * deltaTime;
		for (const auto& platform : platforms) {
			if (collides(platform)) {
				Position.x -= Velocity.x * deltaTime;
				Velocity.x = 0.0f;
				break;
			}
		}

		// ���������� ������� �� Z
		Position.z += Velocity.z * deltaTime;
		for (const auto& platform : platforms) {
			if (collides(platform)) {
				Position.z -= Velocity.z * deltaTime;
				Velocity.z = 0.0f;
				break;
			}
		}

		for (const auto& piramide : piramides) {
			if (collides(piramide)) {
				Position = originalPosition;
				/*Velocity = glm::vec3(0.0f);*/
				if (Velocity.y < 0) { // ���� ������ �� ��������
					onGround = true;
					Velocity.y = 0.0f;
				}
				break;
			}
		}

		// ���������� ����� ������� ������� ������ � ��������� ��������
		/*std::cout << "Camera Position: " << Position.x << ", " << Position.y << ", " << Position.z << std::endl;
		std::cout << "On Ground: " << onGround << std::endl;*/
	}
} // ����������� ������ ��� ������������ ���� Physics

