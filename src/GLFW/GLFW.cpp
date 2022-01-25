#include "GLFW.h";

GLFW::Glfw::Glfw() {

};

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

	window = glfwCreateWindow(getHeight(), getHeight(), "Window 01", NULL, NULL);

	glfwMakeContextCurrent(window);
	gladLoadGL();

	glViewport(0, 0, 700, 700);
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glfwSwapBuffers(window);
	//glfwSwapBuffers(window_02);

	if (window == NULL) {
		cout << "Failed to initialise window." << endl;
		glfwTerminate();
		return -1;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");


	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
			
		ImGui::Begin("Main");
		if (ImGui::Button("Play")) {
			bool isPlaying = true;
			if (isPlaying) {
				cout << "Play Button is working." << endl;
			}
		};
		if (ImGui::Button("Stop")) {
			bool hasStopped = true;
			if (hasStopped) {
				cout << "Stop button is working" << endl;
			}
		}

		/* Slider */
		static float rotation = 0.0;
		float SliderValue = ImGui::SliderFloat("Slider", &rotation, 0, 100);
		//LOG(rotation);

		static float color[4] = {1.0f, 1.0f, 1.0f, 1.0f};

		ImGui::ColorEdit3("color", color);

		ImGui::ShowDemoWindow();
		ImGuiIO &m = ImGui::GetIO();
		
		

		ImGui::End();		
		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
//	glfwDestroyWindow(window_02);
	glfwTerminate();

}

void GLFW::Glfw::DeleteWindow() {

	/*
	glfwDestroyWindow(window);
	glfwTerminate();
	*/
}

GLFW::Glfw::~Glfw() {
	//DeleteWindow();
};