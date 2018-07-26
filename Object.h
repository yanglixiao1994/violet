#pragma once
#include "auxiliary.h"
#include "Mesh.h"
using namespace glm;

class Object {
protected:
	vec3 posi;

	list<ObjPtr>childs;
	ObjPtr      father;

	Mesh         *mesh;

	bool dirty;
	bool visible;
	bool shadow;
public:
	mat4 toWorld;

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

