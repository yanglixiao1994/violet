#pragma once
#include"auxiliary.h"
#include "Object.h"
namespace violet {
	class Light :public Object {
	public:
		vec3 getColor() {
			return _color;
		}
		Light(const vec3&posi, const vec3&color) :Object(posi), _color{color} {}
	private:
		vec3 _color;
	};
	typedef std::shared_ptr<Light>	 LightPtr;
	typedef std::vector<LightPtr>    LightVec;
}