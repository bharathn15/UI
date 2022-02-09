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


unsigned int GLFW::Glfw::CompileShader(unsigned	int type, const string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);

	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		// Memory Allocation
		char* message = (char*)malloc(length * sizeof(char));
		
		LOG("Failed to compile Shader !");
		LOG((type == GL_VERTEX_SHADER ? "Vertex" : "Fragment"));
		LOG(message);
		glDeleteShader(id);
		return 0;
	}
	LOG("Compile Shader Result - " + to_string(result));
	return id;
}

unsigned int GLFW::Glfw::CreateShader(const string& vertexShader, const string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

int GLFW::Glfw::CreateWindow() {
	getHeight();
	getWidth();

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	setWidth(10000);
	setHeight(1000);
	window = glfwCreateWindow(getWidth(), getHeight(), "Window 01", NULL, NULL);

	glfwMakeContextCurrent(window);
	gladLoadGL();

	glViewport(0, 0, 700, 700);

	// Set gray background
	// glClearColor(.5f, .5f, .5f, 0);
	glClearColor(0.0f, 0.0f, 0.0f, 0);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glfwSwapBuffers(window);

	if (window == NULL) {
		cout << "Failed to initialise window." << endl;
		glfwTerminate();
		return -1;
	}
	
	float Positions[6] = {
		-0.5f, -0.5f, 
		0.0f, 0.5f,   
		0.5f, -0.5f  
	};

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), Positions, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT ,GL_FALSE, sizeof(float) * 2, 0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	float f = buffer;
	LOG("Buffer Value is - "+to_string(f));

	string vertexShader =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec4 position;\n"
		"\n"
		"void main()\n"
		"{\n"
		" gl_Position = position;\n"
		"}\n";

	string fragmentShader =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) out vec4 color;"
		"\n"
		"void main()\n"
		"{\n"
		" color = vec4(1.0,0.0,0.0,1.0);\n"
		"}\n";

	unsigned int shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);

	while (!glfwWindowShouldClose(window)) {
		
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
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