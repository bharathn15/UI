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

		/* KeyBoard Input */
		virtual void Input_Key();

		/* Vertex Shader */
		virtual unsigned int Vertex_Shader();

		/* Fragment Shader */
		virtual unsigned int Fragment_Shader();

		virtual int CreateWindow();
		void DeleteWindow();
		~Glfw();

	};
}