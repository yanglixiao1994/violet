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

	Mesh         *mesh;

	bool dirty;
	bool visible;
	bool shadow;
public:

	void reset() {
		toWorld = mat4(1.f);
		for (auto &child : childs) {
			child->reset();
		}
	}
	void scale(const vec3&factor) {
		toWorld = ::scale(toWorld, factor);
		for (auto &child : childs) {
			child->scale(factor);
		}
	}
	void rotate(float deg,const vec3&axis) {
		toWorld = ::rotate(toWorld, deg / 180.0f, axis);
		for (auto &child : childs) {
			child->rotate(deg,axis);
		}
	}
	void move(const vec3&step) {
		toWorld = translate(toWorld, step);
		for (auto &child : childs) {
			child->move(step);
		}
	}

	void setFather(const ObjPtr&obj) {
		father = obj;
	}
	void insertChild(const ObjPtr&obj) {
		childs.push_back(obj);
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
		posi{ posi },
		father{ father },
		mesh{ mesh },
		dirty{ dirty },
		visible{ visible },
		throwshadow{ throwshadow } {};


};
typedef shared_ptr<Object>  ObjPtr;
typedef list<ObjPtr> ObjList;

