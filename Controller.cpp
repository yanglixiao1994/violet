#include "Controller.h"
#include "Object.h"
namespace violet {
	void RambleController::update() {
		static bool firstTime = true;
		float nowTime = getTime();
		_deltaTime = nowTime - _lastTime;
		_lastTime = nowTime;
		//glfwGetCursorPos(window, &_cursorX, &_cursorY);

		//_owner->rotate(vec3{ 0.f, .1f, 0.f });

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
			_owner->move(_deltaTime * _moveSpeed * _owner->getRight());
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			//_owner->move(vec3{ -_deltaTime * _moveSpeed ,0.f,0.f });
			_owner->move(-_deltaTime * _moveSpeed * _owner->getRight());
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
			double newx, newy;
			glfwGetCursorPos(window, &newx, &newy);
			//cout << newx << " " << newy << endl;
			//cout << _cursorX << " " << _cursorY << endl;
			
			if (!firstTime) {
				cout << (newy - _cursorY) * _deltaTime << " f " << (newx - _cursorX) * _deltaTime << endl;
				_owner->rotate(vec3{ (newy - _cursorY) * _deltaTime * _rotateSpeed,(newx - _cursorX) * _deltaTime,0.f });

			}
			firstTime = false;
			_cursorX = newx;
			_cursorY = newy;
		}

	}
}