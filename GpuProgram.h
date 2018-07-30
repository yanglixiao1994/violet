#pragma once
#include "auxiliary.h"

class GpuProgram {
public:
	GLuint id;
	void loadShaders(const string&vShaderPath, const string&fShaderPath);
private:
	void checkCompileErrors(uint32 shader, string type);

	string vertexShaderFile;
	string fragmentShaderFile;
	string vertexCode;
	string fragmentCode;
};