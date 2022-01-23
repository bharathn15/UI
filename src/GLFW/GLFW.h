#pragma once
#include "../Headers.h";


namespace GLFW {
	class Glfw {
	private:
		int width = 900;
		int height = 900;
		
		/* GLFW Window */
		GLFWwindow* window;
		GLFWwindow* window_02;
	public:
		Glfw();
		int getWidth();
		void setWidth(int Height);
		int getHeight();
		void setHeight(int Width);
		virtual int CreateWindow();
		void DeleteWindow();
		~Glfw();

	};
}