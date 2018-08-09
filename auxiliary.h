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
		constexpr vec3 up{ 0,1,0 };
		const vec3 up1{ 0,1,0 };
		static vec3 forward = { 0,0,1 };
		static vec3 right = { 1,0,0 };

		mat4 rotatex(float Degree) {
			float cost = cosf(radians(Degree));
			float sint = sinf(radians(Degree));
			return mat4(
				1.f, 0.f, 0.f, 0.f,
				0.f, cost, -sint, 0.f,
				0.f, sint, cost, 0.f,
				0.f, 0.f, 0.f, 1.f
			);
		}

		mat4 rotatey(float Degree) {
			float cost = cosf(radians(Degree));
			float sint = sinf(radians(Degree));
			return mat4(
				cost, 0.f, -sint, 0.f,
				0.f, 1.f, 0, 0.f,
				sint, 0.f, cost, 0.f,
				0.f, 0.f, 0.f, 1.f
			);
		}

		mat4 rotatez(float Degree) {
			float cost = cosf(radians(Degree));
			float sint = sinf(radians(Degree));
			return mat4(
				cost, -sint, 0.f, 0.f,
				sint, cost, 0.f, 0.f,
				0.f, 0.f, 1.f, 0.f,
				0.f, 0.f, 0.f, 1.f
			);
		}

		mat4 rotate(const vec3&euler) {
			return rotatez(euler.z) * rotatey(euler.y) * rotatex(euler.x);
		}
	}
}