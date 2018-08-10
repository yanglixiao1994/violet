#include "auxiliary.h"
namespace violet {
	GLFWwindow* window;
	double getTime() {
		return glfwGetTime() - 0;
	}
	namespace math {

		float length(const glm::vec3&v) {
			return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
		}

		glm::vec3 normalize(const glm::vec3&v) {
			float inverse = 1 / length(v);
			return glm::vec3{ v.x * inverse,v.y * inverse,v.z * inverse };
		}

		glm::mat4 rotatex(float Degree) {
			float cost = cosf(glm::radians(Degree));
			float sint = sinf(glm::radians(Degree));
			return glm::mat4(
				1.f, 0.f, 0.f, 0.f,
				0.f, cost, -sint, 0.f,
				0.f, sint, cost, 0.f,
				0.f, 0.f, 0.f, 1.f
			);
		}

		glm::mat4 rotatey(float Degree) {
			float cost = cosf(glm::radians(Degree));
			float sint = sinf(glm::radians(Degree));
			return glm::mat4(
				cost, 0.f, -sint, 0.f,
				0.f, 1.f, 0, 0.f,
				sint, 0.f, cost, 0.f,
				0.f, 0.f, 0.f, 1.f
			);
		}

		glm::mat4 rotatez(float Degree) {
			float cost = cosf(glm::radians(Degree));
			float sint = sinf(glm::radians(Degree));
			return glm::mat4(
				cost, -sint, 0.f, 0.f,
				sint, cost, 0.f, 0.f,
				0.f, 0.f, 1.f, 0.f,
				0.f, 0.f, 0.f, 1.f
			);
		}

		glm::mat4 rotate(const glm::vec3&euler) {
			return rotatez(euler.z) * rotatey(euler.y) * rotatex(euler.x);
		}
	}
}