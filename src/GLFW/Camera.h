#pragma once
#include "../Headers.h";


class Camera {

public:
	vec3 Position;
	vec3 Orientation = vec3(0.f, 0.f, -1.f);
	vec3 Up = vec3(0.f, 1.f, 0.f);

	Camera();

	Camera(int width, int height, vec3 position);

	void getViewMatrix(int shaderProgram, float rotation, float prevTime); // vec3 position, vec3 target, vec3 up

	void Matrix(float FOVdeg, int shaderProgram, float nearPlane, float farPlane, const char* uniform);

	void Inputs(GLFWwindow* window);

	void Camera_Pers_View();

	~Camera();
};