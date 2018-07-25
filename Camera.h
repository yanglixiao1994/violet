#pragma once
#include"auxiliary.h"
#include"Object.h"
using namespace glm;
enum class CAM_CONTROL_TYPE {
	FIRST_PERSON,
};
class Camera:public Object{
public:

	mat4& getViewMat() {
		return V;
	}
	mat4& getProjMat() {
		return P;
	}
	void setSight(float near = .1f, float far = 1000.f) {
		near = near;
		far = far;
		update();
	}
	void setLens(float FOV = radians(60), float aspect = 4.f / 3.f) {
		FOV = FOV;
		aspect = aspect;
		update();
	}
	void setSpeed(float move_speed = 3.f, float rotate_speed = .005f) {
		move_speed = move_speed;
		rotate_speed = rotate_speed;
	}
	Camera(const vec3&p = vec3(0, 0, 0), 
		float far = 1000.f, 
		float near = 0.1f, 
		float aspect = 4.f / 3.f,
		float FOV = radians(45), 
		float move_speed = 3.f, 
		float rotate_speed = .005f,
		CAM_CONTROL_TYPE ctr = CAM_CONTROL_TYPE::FIRST_PERSON) :
		Object{ p }, 
		far{far},
		near{near},
		aspect{aspect},
		FOV{FOV},
		move_speed{move_speed},
		rotate_speed{rotate_speed},
		ctr{ctr}
		{
		update();
	}
	virtual void update() {};
private:
	mat4 V;
	mat4 P;
	CAM_CONTROL_TYPE ctr;
	float far, near;
	float aspect;
	float FOV;
	float move_speed;
	float rotate_speed;
};
typedef shared_ptr<Camera>   CamPtr;
typedef list<CamPtr>		CamList;