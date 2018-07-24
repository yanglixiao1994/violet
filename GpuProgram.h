#pragma once
#include "auxiliary.h"

class GpuProgram {
public:
	GLuint id;
	void loadShaders(const string&vShaderPath, const string&fShaderPath);
private:
	string vertexShaderFile;
	string fragmentShaderFile;
	string vertexShaderCode;
	string fragmentShaderCode;
};