#include "Camera.h";

Camera::Camera() {

}

Camera::Camera(vec3 position, vec3 direction, vec3 WorldUp) {

}

void Camera::getViewMatrix() {
	const float radius = 10.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;

	mat4 view;
	view = lookAt(vec3(camX, 0.0, camZ),
				 vec3(0, 0.0, 0),
				 vec3(0, 1.0, 0)
				);
	
	
}

Camera::~Camera() {

}