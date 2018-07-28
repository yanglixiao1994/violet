#pragma once
#include "auxiliary.h"
#include "Mesh.h"
using namespace glm;

class Object {
protected:
	//The relative information
	vec3 _posi;
	vec3 _scaler;
	vec3 _rotate;
	mat4 _toWorld;

	list<ObjPtr>_childs;
	ObjPtr      _father;

	Mesh         *_mesh;

	bool _dirty;
	bool _visible;
	bool _shadow;
public:
	vec3 getPosition() {
		return _posi;
	}

	void reset() {
		_toWorld = mat4(1.f);
		for (auto &child : _childs) {
			child->reset();
		}
	}
	void scale(const vec3&factor) {
		_toWorld = ::scale(_toWorld, factor);
		for (auto &child : _childs) {
			child->scale(factor);
		}
	}
	void rotate(float deg,const vec3&axis) {
		_toWorld = ::rotate(_toWorld, deg / 180.0f, axis);
		for (auto &child : _childs) {
			child->rotate(deg,axis);
		}
	}
	void move(const vec3&step) {
		_toWorld = translate(_toWorld, step);
		for (auto &child : _childs) {
			child->move(step);
		}
	}

	void setFather(const ObjPtr&obj) {
		_father = obj;
	}
	void insertChild(const ObjPtr&obj) {
		_childs.push_back(obj);
	}

	mat4 getToWorldMat();
	virtual void update();

	Object(
		const vec3&posi = vec3{ 0,0,0 },
		Object *father = nullptr,
		Mesh   *mesh = nullptr,
		bool dirty = true,
		bool visible = true,
		bool throwshadow = true
		) :
		_posi{ posi },
		_father{ father },
		_mesh{ mesh },
		_dirty{ dirty },
		_visible{ visible },
		_shadow{ throwshadow } {};


};
typedef shared_ptr<Object>  ObjPtr;
typedef list<ObjPtr> ObjList;

