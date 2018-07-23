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
using namespace std;
using namespace glm;

#define WINDOW_HEIGHT 1024
#define WINDOW_WIDTH 768

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
