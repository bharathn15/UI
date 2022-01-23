#include "Headers.h";
#include "GLFW/GLFW.h";   




int main() {
	/* GLFW */
	GLFW::Glfw* glfw = new GLFW::Glfw();
	
	/* GLFW Window creation */
	glfw->CreateWindow();

	return 0;
}