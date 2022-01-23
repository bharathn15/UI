#include "GLFW.h";


int GLFW::Glfw::getWidth() {
	
	return width;
}

void GLFW::Glfw::setWidth(int Width) {

	width = Width;
}

int GLFW::Glfw::getHeight() {
	
	return height;
}

void GLFW::Glfw::setHeight(int Height) {

	width = Height;
}


int GLFW::Glfw::CreateWindow() {
	getHeight();
	getWidth();

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(getHeight(), getHeight(), "UI Window", NULL, NULL);
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, 700, 700);
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	if (window == NULL) {
		cout << "Failed to initialise window." << endl;
		glfwTerminate();
		return -1;
	}

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

}