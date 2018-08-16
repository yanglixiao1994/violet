#include"Camera.h"

namespace violet {
	static float horizontalAngle = 3.14f;
	static float verticalAngle = 0.0f;
	void Camera::update() {
		for (auto &com : _coms) {
			com->update();
		}
		_P = glm::perspective(_FOV, 4.f / 3.f, _near, _far);
		// Camera matrix
		//cout << getForward().x << " " << getForward().y << " " << getForward().z << endl;
		_V = glm::lookAt(
			_posi, // Camera is at (4,3,3), in World Space
			_posi + vec3(getToWorldMat() * math::forward), // and looks at the origin
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