// ImGui
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// ����������� ����������
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

// ��������� ������ 
#include "Piramide.h"
#include "Platform.h"
#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"
#include "TT.h"

const unsigned int width = 1920;
const unsigned int height = 1080;


// ������������ ����������
GLfloat vertices[] =
{ //     ����������     /        �����          /    ���� ���������  /        �������       //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, 
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, 
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, 
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, 

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, 
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, 
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, 

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, 
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, 
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, 

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, 
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, 
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, 

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, 
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, 
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  
};

// ������� ������� ������
GLuint indices[] =
{
	0, 1, 2, 
	0, 2, 3, 
	4, 6, 5, 
	7, 9, 8, 
	10, 12, 11, 
	13, 15, 14 
};

GLfloat lightVertices[] =
{ //     ����������     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

GLfloat skyVertices[] = {
	// ������� ���������: X, Y, Z
	// ������� �������
	-1.0f,  1.0f, -1.0,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 //������ �������
	 -1.0f,  1.0f,  1.0f,
	 -1.0f, -1.0f,  1.0f,
	  1.0f, -1.0f,  1.0f,
	  1.0f,  1.0f,  1.0f
};

GLuint skyIndices[] = {
	// ����� �������
	0, 1, 5,
	0, 5, 4,
	// ������ �������
	3, 2, 6,
	3, 6, 7,
	// ������� �������
	0, 3, 7,
	0, 7, 4,
	// ������ �������
	1, 2, 6,
	1, 6, 5,
	// ������ �������
	7, 6, 4,
	5, 6, 4,
	// ������� �������
	/*0, 1, 2,
	0, 2, 3*/
};

GLfloat need_1[]{
	-1.0f,  1.0f, -1.0,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f
};

GLuint need_2[] = {
	// ������� �������
	0, 1, 2,
	0, 2, 3
};

GLfloat platformVertices[] = {
	-4.0f, 0.0f,  4.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	-4.0f, 0.0f, -4.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 4.0f, 0.0f, -4.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 4.0f, 0.0f,  4.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
};

GLuint platformIndices[]{
	0, 1, 2,
	0, 2, 3
};


// ���������� ������� ��������� ������
void framebuffer_size_callback(GLFWwindow* window, int width, int height);


int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// �������� GLFW, ��� �� ���������� ������� CORE
	// ��� ��������, ��� � ��� ���� ������ ����������� �������
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(width, height, "HELL", nullptr, nullptr);
	// ������ ������ �������� ����, ���� ���-�� ������ �� ���
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	std::cout << "Program started!" << std::endl;

	// ������ ���� � ������� ��������
	glfwMakeContextCurrent(window);

	//��������� GLAD, ����� �� �������� OpenGL
	gladLoadGL();
	// ��������� ������� ��������� OpenGL � ����
	// � ���� ������ ������� ��������� �������� � x = 0, y = 0 �� x = 1920, y = 1080
	glViewport(0, 0, width, height);
	

	// ���������� ����������� � ��������� �������
	Shader shaderProgram("default.vert", "default.frag");
	Shader lightShader("light.vert", "light.frag");
	Shader skyShader("sun.vert", "sun.frag");
	Shader needShader("need.vert", "need.frag");
	Shader platformShader("platform.vert", "platform.frag");

	// �������� ���
	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	// ������ ��� ������������ ����
	VAO lightVAO;
	lightVAO.Bind();
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	VAO skyVAO;
	skyVAO.Bind();
	VBO skyVBO(skyVertices, sizeof(skyVertices));
	EBO skyEBO(skyIndices, sizeof(skyIndices));
	skyVAO.LinkAttrib(skyVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	skyVAO.Unbind();
	skyVBO.Unbind();
	skyEBO.Unbind();

	VAO needVAO;
	needVAO.Bind();
	VBO needVBO(need_1, sizeof(need_1));
	EBO needEBO(need_2, sizeof(need_2));
	needVAO.LinkAttrib(needVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	needVAO.Unbind();
	needVBO.Unbind();
	needEBO.Unbind();

	// ���������
	VAO platformVAO;
	platformVAO.Bind();
	VBO platformVBO(platformVertices, sizeof(platformVertices));
	EBO platformEBO(platformIndices, sizeof(platformIndices));
	platformVAO.LinkAttrib(platformVBO, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	platformVAO.LinkAttrib(platformVBO, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	platformVAO.LinkAttrib(platformVBO, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	platformVAO.LinkAttrib(platformVBO, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	platformVAO.Unbind();
	platformVBO.Unbind();
	platformEBO.Unbind();

	glEnable(GL_DEPTH_TEST);

	// �������� �����
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	// ��������
	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	// ���������
	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);


	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	platformShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(platformShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(platformShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(platformShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	// ������ ��� ���� � ������
	glfwSetWindowUserPointer(window, &skyShader);
	glfwSetWindowUserPointer(window, &needShader);

	/*glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);*/
	// ��������(��������)
	Texture sandTex("sand.png", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
	sandTex.texUnit(shaderProgram, "tex0", 0);

	//��������(���������)
	Texture platformTex("sand.png", GL_TEXTURE_2D, 1, GL_RGB, GL_UNSIGNED_BYTE);
	platformTex.texUnit(platformShader, "tex1", 1);

	// ������� ������
	Physics::Camera camera(width, height, glm::vec3(0.0f, 0.2f, 3.0f), glm::vec3(0.0f));
	camera.addPlatform(Platform(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(10.0f, 1.0f, 10.0f)));
	camera.addPiramide(PiramideAABB(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.5f, 2.0f, 1.5f)));
	TT::Time time;

	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	// ���������� ��� ������������ FPS
	float fpsUpdateTime = 0.0f;
	int fps = 0;
	int frameCount = 0;
	float averagedFPS = 0.0f;
	

	// ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// �������� ���� while
	while (!glfwWindowShouldClose(window))
	{
		// ���������� �������
		time.update();

		// ���������� deltaTime ��� ������
		float deltaTime = time.getDelta();
		camera.updateDeltaTime(deltaTime);

		// ���������� FPS
		fpsUpdateTime += deltaTime;
		fps++;
		frameCount++;

		// ��������� FPS ������ 0.5 �������
		if (fpsUpdateTime >= 0.5f) {
			averagedFPS = fps / fpsUpdateTime;
			/*std::string fpsTitle = "OpenGL FPS: " + std::to_string(static_cast<int>(averagedFPS));
			glfwSetWindowTitle(window, fpsTitle.c_str());*/
			fpsUpdateTime = 0.0f;
			fps = 0;
		}


		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		if (height == 0) {
			height = 1;
		}

		// ��������� ����������� ������
		float aspect = static_cast<float>(width) / static_cast<float>(height);

		// ��������� ���� ����
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// ��������� ������� ��� ����, ����� ��� ����������� ������ ���� ��������
		glDepthFunc(GL_LEQUAL);

		// ��������� ���� (����+c�����(����� �������, ��� ��� �����!))
		glDepthMask(GL_FALSE); // ��������� ������ � ����� �������
		skyShader.Activate();
		skyVAO.Bind();
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
		glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(skyShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skyShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glDrawElements(GL_TRIANGLES, sizeof(skyIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
		skyVAO.Unbind();
		glDepthMask(GL_TRUE); // �������� ������ � ����� �������

		// ����������� ������� ������� ������� � ����������� ��������
		glDepthFunc(GL_LESS);

		// ������
		glDepthFunc(GL_LEQUAL);

		glDepthMask(GL_FALSE); // ��������� ������ � ����� �������
		// ����(������� �������)
		needShader.Activate();
		needVAO.Bind();
		glm::mat4 projection_1 = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(needShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection_1));
		glm::mat4 view_1 = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(needShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view_1));
		glDrawElements(GL_TRIANGLES, sizeof(need_2) / sizeof(int), GL_UNSIGNED_INT, 0);
		needVAO.Unbind();

		glDepthMask(GL_TRUE); // �������� ������ � ����� �������

		// ����������� ������� ������� ������� � ����������� ��������
		glDepthFunc(GL_LESS);

		// ���������
		shaderProgram.Activate();
		// ������������ ��������� ������ �� ����������� ������ ��� ����������� ���������
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");
		sandTex.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		// ��� �����
		lightShader.Activate();
		glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		camera.Matrix(lightShader, "camMatrix");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		// ���������
		platformShader.Activate();
		glUniform3f(glGetUniformLocation(platformShader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(platformShader, "camMatrix");
		platformTex.Bind();
		platformVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(platformIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		// �������� �������� � ����������
		for (const auto& piramide : camera.piramides) {
			camera.collides(piramide);
		}

		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR) {
			std::cout << "OpenGL error: " << err << std::endl;
		}

		// ImGui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("HELL Project");
		ImGui::Text("Welcome to my project! HELL");
		ImGui::Text("OpenGL FPS: %.1f", averagedFPS);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// ��� ���������
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// ������� ��� ������� ������� �������
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	skyVAO.Delete();
	skyVBO.Delete();
	skyEBO.Delete();
	needVAO.Delete();
	needVBO.Delete();
	needEBO.Delete();
	platformVAO.Delete();
	platformVBO.Delete();
	platformEBO.Delete();
	sandTex.Delete();
	platformTex.Delete();
	shaderProgram.Delete();
	lightShader.Delete();
	skyShader.Delete();
	needShader.Delete();
	platformShader.Delete();
	// Imgui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	// �������� ����
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}