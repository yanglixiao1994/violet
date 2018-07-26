#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
using namespace std;

#define WINDOW_HEIGHT 1024
#define WINDOW_WIDTH 768

typedef unsigned int uint32;
typedef unsigned long uint64;
typedef unsigned short uint16;
typedef unsigned char uint8;

typedef map<std::string, glm::vec3> Param3f;
typedef map<std::string, vector<glm::vec3>> Param3vf;
typedef map<std::string, glm::vec2> Param2f;
typedef map<std::string, vector<glm::vec2>> Param2vf;
typedef map<std::string, float> Param1f;
typedef map<std::string, vector<float>> Param1vf;

typedef map<std::string, vector<int>> Param1i;

#ifdef NDEBUG
#define Assert(expr) expr
#else
#define Assert(expr) assert(expr)
#endif
static double start_time = glfwGetTime();
GLFWwindow* window;
//Get the last time of the Application
double getTime() {
	return glfwGetTime() - start_time;
}
