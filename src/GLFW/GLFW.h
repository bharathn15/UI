#pragma once
#include "../Headers.h";
#include "Camera.h";
#include "../src/GLFW/stb_image.h";
#include "shader_s.h";

namespace GLFW {
	class Glfw : public Camera {
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
		bool is_KeyPressed = false;
		/* KeyBoard Input */
		virtual void Input_Key();

		/* Update Input */
		virtual void KeyboardInput(GLFWwindow* window);

		/* Camera */
		virtual void Camera_Position();

		/* Textures */
		virtual void Texture();

		virtual void Move_Triangle(GLFWwindow* window);

		/* Loading 3D modeling */
		virtual void Load_Model();

		/* Mouse Input  */
		//virtual void mouseButtonCallback(GLFWwindow* window);

		/* Vertex Shader */
		virtual unsigned int Vertex_Shader();

		/* Fragment Shader */
		virtual unsigned int Fragment_Shader();

		virtual int CreateWindow();
		void DeleteWindow();

		static void Get_Vertex_Shader(const string& filePath);

		~Glfw();

	};
}