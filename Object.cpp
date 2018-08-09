#include"Object.h"
namespace violet {

	mat4 Object::localToParent() {
		return glm::mat4(//transit
			glm::vec4(1.f, 0.f, 0.f, 0.f),
			glm::vec4(0.f, 1.f, 0.f, 0.f),
			glm::vec4(0.f, 0.f, 1.f, 0.f),
			glm::vec4(_posi.x, _posi.y, _posi.z, 1.f))
			* math::rotatez(_rotate.z)//rotate
			* math::rotatey(_rotate.y)
			* math::rotatex(_rotate.x)
		*glm::mat4(//scale
			glm::vec4(_scaler.x, 0.f, 0.f, 0.f),
			glm::vec4(0.f, _scaler.y, 0.f, 0.f),
			glm::vec4(0.f, 0.f, _scaler.z, 0.f),
			glm::vec4(0.f, 0.f, 0.f, 1.f));
	}

	mat4 Object::getToWorldMat() {
		if(_parent.get())
			return _parent->getToWorldMat() * localToParent();
		return localToParent();
	}

	vec3 Object::getForward() {
		stack<vec3>rotates;
		ObjPtr now = shared_from_this();
		mat4 finalMat = mat4{1.f};
		while(now.get()) {
			rotates.push(now->rotate);
			now = now->_parent;
		}
		while (!rotates.empty()) {
			finalMat *= math::rotate(rotates.top());
			rotates.pop();
		}
		return finalMat * ;
	}
}