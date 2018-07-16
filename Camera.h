#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
class Camera {
public:
	mat4 V;
	mat4 P;
	vec3 posi;

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
	Camera(const vec3&p = vec3(0, 0, 0), float far = 1000.f, float near = 0.1f, float aspect = 4.f / 3.f,
		float FOV = radians(45), float move_speed = 3.f, float rotate_speed = .005f) {
		update();
	}
	virtual void update() {};
private:

	float far, near;
	float aspect;
	float FOV;
	float move_speed;
	float rotate_speed;
};