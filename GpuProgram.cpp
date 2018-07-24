#include "GpuProgram.h"

void GpuProgram::loadShaders(const string&vertexPath, const string&fragmentPath) {
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	GLuint vertexid, fragmentid;
	vertexid = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexid, 1, &vShaderCode, 0);
	glCompileShader(vertexid);
	int success;
	glGetShaderiv(vertexid, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(vertexid, 512, NULL, infoLog);
		std::cout << "ERROR Compile vertexshader:" << infoLog << std::endl;
	}
	
	fragmentid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentid, 1, &fShaderCode, 0);
	glCompileShader(fragmentid);
	glGetShaderiv(fragmentid, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(vertexid, 512, NULL, infoLog);
		std::cout << "ERROR Compile fragmentshader:" << infoLog << std::endl;
	}
	id = glCreateProgram();
	glAttachShader(id, vertexid);
	glAttachShader(id, fragmentid);
	glLinkProgram(id);
	glGetShaderiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(vertexid, 512, NULL, infoLog);
		std::cout << "ERROR Link shader program:" << infoLog << std::endl;
	}
	glDeleteShader(vertexid);
	glDeleteShader(fragmentid);

}