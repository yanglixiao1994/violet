#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
#include <iostream>
#include <memory>
#include <math.h>
#include <fstream>
#include <sstream>
#include <initializer_list>
#include <functional>
using namespace std;
namespace violet {

	typedef unsigned int uint32;
	typedef unsigned long uint64;
	typedef unsigned short uint16;
	typedef unsigned char uint8;

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

#ifdef NDEBUG
#define Assert(expr) expr
#else
#define Assert(expr) assert(expr)
#endif
	extern GLFWwindow* window;
	//Get the last time of the Application
	double getTime();

	template<typename Enum>
	Enum operator |(Enum lhs, Enum rhs) {
		static_assert(std::is_enum<Enum>::value, "template parameter is not an enum type");
		using underlying = typename std::underlying_type<Enum>::type;
		return static_cast<Enum>(
			static_cast<underlying>(lhs) |
			static_cast<underlying>(rhs)
			);
	}

	template<typename T>
	bool is_in(const T&t, const std::initializer_list<T>&list) {
		for (const auto &tt : list) {
			if (tt == t)return true;
		}
		return false;
	}
	namespace math {
		const glm::vec4 up{ 0,1,0,0 };
		const glm::vec4 forward = { 0,0,1,0 };
		const glm::vec4 right = { 1,0,0,0 };

		float length(const glm::vec3&v);

		glm::vec3 normalize(const glm::vec3&v);

		glm::mat4 rotatex(float Degree);

		glm::mat4 rotatey(float Degree);

		glm::mat4 rotatez(float Degree);

		glm::mat4 rotate(const glm::vec3&euler);
	}
}