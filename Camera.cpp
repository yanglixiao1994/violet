#include"Camera.h"

namespace violet {
	static float horizontalAngle = 3.14f;
	static float verticalAngle = 0.0f;
	void Camera::update() {
		_P = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
		// Camera matrix
		_V = glm::lookAt(
			glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
	}
	string Camera::getName() {
		return _name;
	}
	//TODO:Using a space management structure.
	bool Camera::isInView(const ObjPtr&obj) {
		return true;
	}

}