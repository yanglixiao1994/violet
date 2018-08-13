#include "Controller.h"
#include "Object.h"
namespace violet {
	void RambleController::update() {
		float nowTime = getTime();
		_deltaTime = nowTime - _lastTime;
		_lastTime = nowTime;

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			exit(0);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			//_owner->move(vec3{ 0.f,0.f,_deltaTime * _moveSpeed });
			_owner->move(_deltaTime * _moveSpeed * _owner->getForward());

		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			//_owner->move(vec3{ 0.f,0.f,- _deltaTime * _moveSpeed });
			_owner->move(-_deltaTime * _moveSpeed * _owner->getForward());

		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			//_owner->move(vec3{ _deltaTime * _moveSpeed ,0.f,0.f});
			_owner->move(-_deltaTime * _moveSpeed * _owner->getRight());

		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			//_owner->move(vec3{ -_deltaTime * _moveSpeed ,0.f,0.f });
			_owner->move(_deltaTime * _moveSpeed * _owner->getRight());
		}


	}
}