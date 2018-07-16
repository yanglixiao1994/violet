#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<GL/GL.h>
#include<GL/glew.h>
#include"material.h"
using namespace glm;
class Object {
public:
	mat4 model_mat;
	void reset() {
		model_mat = mat4(1.f);
	}
	virtual void rotate(float deg,const vec3&axis) {
		model_mat = ::rotate(model_mat, deg / 180.0f, axis);
	}
	virtual void move(const vec3&step) {
		model_mat = translate(model_mat, step);
	}
	virtual void scale(const vec3&factor) {
		model_mat = ::scale(model_mat, factor);
	}
	virtual void update() {};
protected:
	vec3 posi;
	Material *matl;

};

class StaticObj :Object {
	
};

