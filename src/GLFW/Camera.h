#pragma once
#include "../Headers.h";


class Camera {
private :

	vec4 ViewMatrix;

	vec3 WorldUp;
	vec3 position = vec3(0.f, 0.f, 3.f);
	vec3 target = vec3(0.f, 0.f, 0.f);
	vec3 up = vec3(0.f, 1.f, 0.f);
	vec3 front;
	vec3 right;
	

	GLfloat movementSpeed;
	GLfloat sensitivity;

	GLfloat pitch;
	GLfloat raw;
	GLfloat yawn;

	void UpdateCameraVectors();

public:
	Camera();

	Camera(vec3 position, vec3 direction, vec3 WorldUp);
	
	void getViewMatrix(); // vec3 position, vec3 target, vec3 up

	~Camera();
};