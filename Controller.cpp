#include "Controller.h"
#include "Object.h"
namespace violet {
	double RambleController::_scrollPos = 0;

	RambleController::RambleController(float moveSpeed, float lookAroundSpeed, float zoomSpeed, float slideAroundSpeed)
		:_moveSpeed{ moveSpeed }, _lookAroundSpeed{ lookAroundSpeed },
		_zoomSpeed{ zoomSpeed }, _slideAroundSpeed{ slideAroundSpeed } {
		glfwSetScrollCallback(window,
			[](GLFWwindow* windows, double, double Y) {
			_scrollPos = Y;
		});
	}

	void RambleController::update() {
		static bool lookAround	= false;
		static bool slideAround = false;
		static bool zoomIn		= false;

		float nowTime = getTime();
		_deltaTime = nowTime - _lastTime;
		_lastTime = nowTime;
		//glfwGetCursorPos(window, &_cursorX, &_cursorY);

		double newx, newy;
		glfwGetCursorPos(window, &newx, &newy);

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
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS) {
			
		}
		auto leftButton = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
		switch (leftButton) {
			case GLFW_PRESS: {
				if (lookAround) {
					_owner->rotate(vec3{ (newy - _cursorY) * _deltaTime * _lookAroundSpeed,
						-(newx - _cursorX) * _deltaTime * _lookAroundSpeed,0.f });
				}
				lookAround = true;
				_cursorX = newx;
				_cursorY = newy;
				break;
			}
			case GLFW_RELEASE: {
				lookAround = false;
				break;
			}
		}

		auto midButton = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE);
		switch (midButton) {
			case GLFW_PRESS: {
				if (slideAround) {
					_owner->move(_owner->getRight() * static_cast<float>(newx - _cursorX) * _slideAroundSpeed);
					_owner->move(_owner->getUp() * static_cast<float>(newy - _cursorY) * _slideAroundSpeed);
				}
				slideAround = true;
				_cursorX = newx;
				_cursorY = newy;
				break;
			}
			case GLFW_RELEASE: {
				slideAround = false;
				break;
			}
		}

		_owner->move(_owner->getForward() * static_cast<float>(_scrollPos) * _zoomSpeed);
		_scrollPos = 0;
	}
}