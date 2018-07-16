#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
using namespace std;
using namespace glm;
static double start_time = glfwGetTime();
double getTime() {
	return glfwGetTime() - start_time;
}