#include"Object.h"
namespace violet {

	mat4 Object::localToParent() {
		return glm::mat4(//for translation
			//glm::vec4(1.f, 0.f, 0.f, _posi.x),
			//glm::vec4(0.f, 1.f, 0.f, _posi.y),
			//glm::vec4(0.f, 0.f, 1.f, _posi.z),
			//glm::vec4(0.f, 0.f, 0.f, 1.f))
			glm::vec4(1.f, 0.f, 0.f, 0.f),
			glm::vec4(0.f, 1.f, 0.f, 0.f),
			glm::vec4(0.f, 0.f, 1.f, 0.f),
			glm::vec4(_posi.x, _posi.y, _posi.z, 1.f))
			* rotatez(_rotate.z)
			* rotatey(_rotate.y)
			* rotatex(_rotate.x)
		*glm::mat4(//for scale
			glm::vec4(_scaler.x, 0.f, 0.f, 0.f),
			glm::vec4(0.f, _scaler.y, 0.f, 0.f),
			glm::vec4(0.f, 0.f, _scaler.z, 0.f),
			glm::vec4(0.f, 0.f, 0.f, 1.f));
	}

	mat4 Object::rotatex(float theta) {
		float cost = cosf(radians(theta));
		float sint = sinf(radians(theta));
		return mat4(
			1.f, 0.f, 0.f, 0.f,
			0.f, cost, -sint, 0.f,
			0.f, sint, cost, 0.f,
			0.f, 0.f, 0.f, 1.f
		);
	}

	mat4 Object::rotatey(float theta) {
		float cost = cosf(radians(theta));
		float sint = sinf(radians(theta));
		return mat4(
			cost, 0.f, -sint, 0.f,
			0.f, 1.f, 0, 0.f,
			sint, 0.f, cost, 0.f,
			0.f, 0.f, 0.f, 1.f
		);
	}

	mat4 Object::rotatez(float theta) {
		float cost = cosf(radians(theta));
		float sint = sinf(radians(theta));
		return mat4(
			cost, -sint, 0.f, 0.f,
			sint, cost, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f
		);
	}

	mat4 Object::getToWorldMat() {
		if(_parent.get())
			return _parent->getToWorldMat() * localToParent();
		return localToParent();
	}
}