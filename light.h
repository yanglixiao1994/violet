#pragma once
#include"auxiliary.h"

class Light {
public:
	vec3 posi;
	vec3 color;
};
typedef shared_ptr<Light>	 LightPtr;
typedef vector<LightPtr>  LightVec;