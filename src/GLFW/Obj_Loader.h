#pragma once
#include "../Headers.h";
#include "Vertex.h";

class Obj_Loader {

private:
	FILE* file;
	string path = "D:\Test.Obj";
	
public:
	static vector<Vertex> Obj_Load_File(const char* file_name);
};