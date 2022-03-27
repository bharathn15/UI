#include<iostream>
#include<string>
#include<sstream>

#include<glad/glad.h>
//#include<glew.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include<glm/mat4x4.hpp>


//#include<gl/GL.h>

#include<GLFW/glfw3.h>
#include "imgui.h";
#include "imgui_impl_glfw.h";
#include "imgui_impl_opengl3.h";
#include "../src/GLFW/stb_image.h";
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

// #include "../src/GLFW/Shader.h";
#include <filesystem>
//#include<glew.h>
#include<glm/glm.hpp>

#include<vector>

#define PI 3.14;
#define LOG(X) std::cout<< X << std::endl;


using namespace std;
using namespace glm;
using namespace Assimp;