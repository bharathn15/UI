#pragma once
#include "../Headers.h";

// bool isPlaying;
// bool hasStopped;


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

		/* Shader Compilation */
		unsigned int CompileShader(unsigned	int type, const string& source);

		/* Shader Creation */
		unsigned int CreateShader(const string& vertexShader, const string& fragmentShader);

		virtual int CreateWindow();
		void DeleteWindow();
		~Glfw();

	};
}