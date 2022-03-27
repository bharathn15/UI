#include "Camera.h";

Camera::Camera() {

}

Camera::Camera(int width, int height, vec3 position) {
	width = width;
	height = height;
	Position = position;
}

void Camera::getViewMatrix(int shaderProgram, float rotation, float prevTime) {
	
	double crnTime = glfwGetTime();
	if (crnTime - prevTime >= 1 / 60) {
		rotation += 0.5f;
		prevTime = crnTime;
	}

	mat4 model = mat4(1.0);
	mat4 view = mat4(1.0);
	mat4 proj = mat4(1.0);

	model = rotate(model, radians(rotation), vec3(0.0f, 1.0f, 0.0f));
	view = translate(view, vec3(0.0f, -0.5f, -2.0f));
	proj = perspective(radians(45.0f), (float)(850/850), 0.1f, 100.0f);

    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

	int viewLoc = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));

	int projLoc = glGetUniformLocation(shaderProgram, "proj");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(proj));


}

void Camera::Matrix(float FOVdeg, int shaderProgram , float nearPlane, float farPlane, const char* uniform) {
	
	mat4 view = mat4(1.0f);
	mat4 projection = mat4(1.0f);

	view = lookAt(Position, Position + Orientation, Up);
	projection = perspective(radians(FOVdeg), (float)(500/500), nearPlane, farPlane);

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, value_ptr(projection * view));
}

void Camera::Inputs(GLFWwindow * window) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		LOG("W Key pressed for the Camera.");
		Position += 10.f * Orientation;
	}
}

void Camera::Camera_Pers_View() {
	
	mat4 Proj = perspective(glm::radians(45.0f), (float)500 / (float)500, 0.1f, 100.0f);

}

Camera::~Camera() {

}