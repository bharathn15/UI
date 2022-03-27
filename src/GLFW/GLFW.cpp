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
"uniform mat4 translate;\n"

"// uniform mat4 model;\n"
"// uniform mat4 view;\n"
"// uniform mat4 proj;\n"

"// uniform mat4 camMatrix;\n"

"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   Vec_Color = vec4(0.0f, 0.0f, 1.0f, 0.0f);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"

"in vec4  Vec_Color;\n"
"out vec4 FragColor;\n"

"void main()\n"
"{\n"
"   FragColor = Vec_Color;\n"
"}\n\0";

string Vertex_ShaderSource = "";

void GLFW::Glfw::Get_Vertex_Shader(const string& filePath) {
    ifstream stream(filePath);
    string line;
    string end_Line = "\n";

    while (getline(stream, line)) {
        Vertex_ShaderSource += line;
        //LOG(line);
        
    }
    LOG(line);
}


const char* VS = Vertex_ShaderSource.c_str();

unsigned int GLFW::Glfw::Vertex_Shader() {
    
    int success;
    char infoLog[512];
    
    Get_Vertex_Shader("src/GLFW/Vertex_Shader.shader");

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER); // Vertex Shader Id
    LOG("Vertex Shader ID - "+to_string(vertexShader));
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // &vertexShaderSource
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

    // build and compile our shader zprogram
    // ------------------------------------
    //Shader ourShader("7.1.camera.vs", "7.1.camera.fs");

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

    //link shaders
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
        -0.5f, -0.5f, 0.0f, // 0   
         0.5f, -0.5f, 0.0f, // 1
         0.5f,  0.5f, 0.0f, // 2 
        
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,  
        -0.5f, -0.5f, 0.0f
    };
    
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // 0.5f,  0.5f, 0.0f,
    // -0.5f, -0.5f, 0.0f


    auto Float_Size = sizeof(float);
    auto Unsigned_Int_Size = sizeof(unsigned int);

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
    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * Unsigned_Int_Size, indices, GL_STATIC_DRAW);

    float texCoords[] = {
    0.0f, 0.0f,  // lower-left corner  
    1.0f, 0.0f,  // lower-right corner
    0.5f, 1.0f   // top-center corner
    };

    // update the uniform color
    Texture();

    // Loading the 3D Model
    // Load_Model();

    float rotation = 0.0f;
    float prevTime = glfwGetTime();

    //Shader ourShader("4.1.texture.vs", "4.1.texture.fs");

    while (!glfwWindowShouldClose(window))
    {
        is_KeyPressed = true;

        // render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        // ourShader.use();

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "Vec_Color");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        // KeyBoard Input
        KeyboardInput(window);

        // Mouse Input
        // mouseButtonCallback(window);

        
        // Camera
        // Camera::getViewMatrix(shaderProgram, rotation, prevTime);

        // Camera::Inputs(window);
        // Camera::Matrix(45, shaderProgram, 0.1f, 100.f, "camMatrix");

        
        double crnTime = glfwGetTime();
        if (crnTime - prevTime >= 1 / 60) {
            rotation += 0.5f;
            prevTime = crnTime;
        }

        
        Move_Triangle(window);

        mat4 model = mat4(1.0);
        mat4 view = mat4(1.0);
        mat4 proj = mat4(1.0);

        // model = rotate(model, radians(rotation), vec3(0.0f, 1.0f, 0.0f));
        float FOV = 45.0f;
        view = translate(view, vec3(0.0f, -0.5f, -2.0f));
        proj = perspective(radians(FOV), (float)(500 / 500), 0.1f, 100.0f);

        // int modelLoc = glGetUniformLocation(shaderProgram, "model");
        // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

        // int viewLoc = glGetUniformLocation(shaderProgram, "view");
        // glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));

        // int projLoc = glGetUniformLocation(shaderProgram, "proj");
        // glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(proj));
        
        // Getting the View Matrix of the Camera
        // getViewMatrix();

        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) * Float_Size/2);

        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

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
    // glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void GLFW::Glfw::Move_Triangle(GLFWwindow* window) {

    mat4 mTranslate = mat4(1.0);
    vec3 offset = vec3(0.03f, 0.0f, 0.0f);
    mTranslate = translate(mTranslate, offset);
    

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        // mat4(mTranslte, "translate");
        LOG(mTranslate.length);
        // LOG("Triangle is Moving to Right.");
    }

}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void GLFW::Glfw::Texture() {

    // load and generate the texture
    int width;
    int height;
    int nrChannels;
    string file_Name = "wall.png";
     
    unsigned char* data = stbi_load(file_Name.c_str(), &width, &height, &nrChannels, 0);
           
    // LOG(data[0]);
    // data is NULL or unable to read the data value. 
    // 0x000000
       
    if (data)
    {   
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
           
    } 
    else
    { 
        LOG("Failed to load texture");
    } 

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // S = X
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // T = Y

    stbi_image_free(data);
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


void GLFW::Glfw::Load_Model() {
    Importer import;
    string path = "wall.png";
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        LOG("Error Loading the Scene or Model - ");
        LOG(import.GetErrorString());
        return;
    }
    else {
        LOG("Model File path is correct.");
    }

    

}

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