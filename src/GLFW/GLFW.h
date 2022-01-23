#pragma once
#include "../Headers.h";


namespace GLFW {
	class Glfw {
	private:
		int width = 900;
		int height = 900;
	public:
		int getWidth();
		void setWidth(int Height);
		int getHeight();
		void setHeight(int Width);
		int CreateWindow();


	};
}