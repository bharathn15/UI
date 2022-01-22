#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

using namespace std;

int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(700, 700, "GLFW-Window", NULL, NULL);
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0,0, 700,700);

	if (window == NULL) {
		cout<< "Failed to initialise window." << endl;
		glfwTerminate();
		return -1;
	}

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}