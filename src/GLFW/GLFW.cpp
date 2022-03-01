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

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 Vec_Color;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   Vec_Color = vec4(0.5f, 0.0f, 0.0f, 1.0f);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4  Vec_Color;\n"
"void main()\n"
"{\n"
"   FragColor = Vec_Color;\n"
"}\n\0";


unsigned int GLFW::Glfw::Vertex_Shader() {
    int success;
    char infoLog[512];

    
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER); // Vertex Shader Id
    LOG("Vertex Shader ID - "+to_string(vertexShader));
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        // std::cout <<  << infoLog << std::endl;
        LOG("ERROR::SHADER::VERTEX::COMPILATION_FAILED");
        LOG(infoLog);
    }
    return vertexShader;
}

unsigned int GLFW::Glfw::Fragment_Shader() {
    int success;
    char infoLog[512];

    // Generating a Fragment Shader ID
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    LOG("Fragment Shader ID - " + to_string(fragmentShader));
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        LOG("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED");
        LOG(infoLog);
    }
    return fragmentShader;
}

int GLFW::Glfw::CreateWindow() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int major, minor, revision;
    glfwGetVersion(&minor, &major, &revision);
    LOG("Minor Version - "+ to_string(minor));
    LOG("Major Version - " + to_string(major));
    LOG("Revision Version - " + to_string(revision));

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // ------------------------------------
    // vertex shader 
    unsigned int VS = Vertex_Shader();
    
    // fragment shader
    unsigned int FS = Fragment_Shader();

    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, VS);
    glAttachShader(shaderProgram, FS);
    
    // Link Program
    glLinkProgram(shaderProgram);
    // check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    // Deleting the Shader
    glDeleteShader(VS);
    glDeleteShader(FS);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    };
    

    auto Float_Size = sizeof(float);

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * Float_Size, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------

    float texCoords[] = {
    0.0f, 0.0f,  // lower-left corner  
    1.0f, 0.0f,  // lower-right corner
    0.5f, 1.0f   // top-center corner
    };

    

    while (!glfwWindowShouldClose(window))
    {

        is_KeyPressed = true;

        // render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);


        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "Vec_Color");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        // KeyBoard Input
        KeyboardInput(window);

        // Mouse Input
        // mouseButtonCallback(window);

        // Camera Position 
        Camera_Position();

        // Getting the View Matrix of the Camera
        getViewMatrix();

        // update the uniform color
        Texture();


        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0); // no need to unbind it every time 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------


        



        glfwSwapInterval(1);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }



    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}



void GLFW::Glfw::Texture() {
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // S = X
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // T = Y
    // load and generate the texture
    int width;
    int height;
    int nrChannels;
    string file_Name = "container.jpg";
   
    unsigned char* data = stbi_load("Test.png", &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        LOG("Failed to load texture");
    }
}




void GLFW::Glfw::KeyboardInput(GLFWwindow* window) {
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        LOG("W Key is Pressed.");
    }
    
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        LOG("E Key is Pressed.");        
    }

    if (glfwGetKey(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        LOG("Left Mouse Button is clicked.");
    }

    double xpos, ypos;
    //getting cursor position
    glfwGetCursorPos(window, &xpos, &ypos);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}


void GLFW::Glfw::Camera_Position() {
    vec3 Camera_Position = vec3(0.f, 0.f, 3.f);   
    vec3 Camera_Target = vec3(0.f, 0.f, 0.f);
    vec3 Camer_Placement = normalize(Camera_Position - Camera_Target);
    //LOG( "Camera X Position - ");
    
}

/*
void GLFW::Glfw::mouseButtonCallback(GLFWwindow* window) {
    int button = NULL;
    int action = NULL;
    int modS = NULL;
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        std::cout << "Right button pressed" << std::endl;
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
        std::cout << "Right button released" << std::endl;
}
*/




void GLFW::Glfw::Input_Key() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	    
    }
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