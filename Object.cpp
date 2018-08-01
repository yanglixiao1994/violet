#include"Object.h"
namespace violet {

	mat4 Object::localToParent() {
		return glm::mat4(//for translation
			glm::vec4(1.f, 0.f, 0.f, 0.f),
			glm::vec4(1.f, 0.f, 0.f, 0.f),
			glm::vec4(1.f, 0.f, 0.f, 0.f),
			glm::vec4(_posi, 0.f)
		) * glm::mat4(//for rotate
			glm::vec4(_rotate.x, 0.f, 0.f, 0.f),
			glm::vec4(0.f, _rotate.y, 0.f, 0.f),
			glm::vec4(0.f, 0.f, _rotate.z, 0.f),
			glm::vec4(0.f, 0.f, 0.f, 1.f)
		)*glm::mat4(//for scale
			glm::vec4(_scaler.x, 0.f, 0.f, 0.f),
			glm::vec4(0.f, _scaler.y, 0.f, 0.f),
			glm::vec4(0.f, 0.f, _scaler.z, 0.f),
			glm::vec4(0.f, 0.f, 0.f, 1.f)
		);
	}

	mat4 Object::getToWorldMat() {
		if(_parent)
			return _parent->getToWorldMat() * localToParent();
		return localToParent();
	}
}