#pragma once
#include"auxiliary.h"
//For convenience of update shader's uniform parameter.
class Lights {
public:
	vector<vec3> posis;
	vector<vec3> colors;
	virtual void update() {};
	void insert(const vec3&posi, const vec3&color) {
		posis.push_back(posi);
		colors.push_back(color);
	}
	void erase(int i) {
		posis.erase(posis.begin() + i);
		colors.erase(colors.begin() + i);
	}
};