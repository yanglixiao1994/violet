#pragma once
#include "auxiliary.h"
#include"Camera.h"
#include"RenderIayer.h"
#include "Mesh.h"
using namespace glm;

class Object {
protected:
	vec3 posi;

	list<Object*>childs;
	Object      *father;

	Mesh          *mesh;

	bool dirty;
	bool visible;
	bool throwshadow;
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

	void setFather(Object *obj) {
		father = obj;
	}
	void insertChild(Object *obj) {
		childs.push_back(obj);
	}

	virtual void update();
	virtual void shot(const Camera&);

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


