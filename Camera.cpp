#include"Camera.h"

namespace violet {
	static float horizontalAngle = 3.14f;
	static float verticalAngle = 0.0f;
	void Camera::update() {
		// deltaTime
		static double lastTime = glfwGetTime();
		double currentTime = glfwGetTime();
		float deltaTime = float(currentTime - lastTime);
		lastTime = currentTime;
		switch (_ctr) {
		case CAM_CONTROL_TYPE::FIRST_PERSON: {
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			glfwSetCursorPos(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

			// Compute new orientation
			horizontalAngle += _rotate_speed * float(WINDOW_WIDTH / 2 - xpos);
			verticalAngle += _rotate_speed * float(WINDOW_HEIGHT / 2 - ypos);

			// Direction : Spherical coordinates to Cartesian coordinates conversion
			glm::vec3 direction(
				cos(verticalAngle) * sin(horizontalAngle),
				sin(verticalAngle),
				cos(verticalAngle) * cos(horizontalAngle)
			);

			// Right vector
			glm::vec3 right = glm::vec3(
				sin(horizontalAngle - 3.14f / 2.0f),
				0,
				cos(horizontalAngle - 3.14f / 2.0f)
			);

			// Up vector
			glm::vec3 up = glm::cross(right, direction);

			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
				_posi += direction * deltaTime * _move_speed;
			}
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
				_posi -= direction * deltaTime * _move_speed;
			}
			if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
				_posi += right * deltaTime * _move_speed;
			}

			if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
				_posi -= right * deltaTime * _move_speed;
			}

			_P = glm::perspective(_FOV, _aspect, _near, _far);
			_V = glm::lookAt(
				_posi,
				//_posi + direction,
				vec3(0,0,0),
				//up
				vec3(0,1,0)
			);
			break;
		}
		}
	}
	string Camera::getName() {
		return _name;
	}
	//TODO:Using a space management structure.
	bool Camera::isInView(const ObjPtr&obj) {
		return true;
	}

}