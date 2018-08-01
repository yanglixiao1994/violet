#pragma once
#include"auxiliary.h"
#include"Object.h"
namespace violet {
	using namespace glm;
	enum class CAM_CONTROL_TYPE {
		FIRST_PERSON,
	};
	/*
	Every camera should have a name, we can set a current camera in scene throw the name.
	*/
	class Camera :public Object {
	public:
		void update();
		string getName();
		mat4 & getViewMat() {
			return _V;
		}
		mat4& getProjMat() {
			return _P;
		}
		void setSight(float near = .1f, float far = 1000.f) {
			_near = near;
			_far = far;
			update();
		}
		void setLens(float FOV = radians(60), float aspect = 4.f / 3.f) {
			_FOV = FOV;
			_aspect = aspect;
			update();
		}
		void setSpeed(float move_speed = 3.f, float rotate_speed = .005f) {
			_move_speed = move_speed;
			_rotate_speed = rotate_speed;
		}
		Camera(const vec3&p = vec3(0, 0, 0),
			const string&name = {"defalut"},
			float far = 1000.f,
			float near = 0.1f,
			float aspect = 4.f / 3.f,
			float FOV = radians(45.f),
			float move_speed = 3.f,
			float rotate_speed = .005f,
			CAM_CONTROL_TYPE ctr = CAM_CONTROL_TYPE::FIRST_PERSON) :
			Object{ p },
			_name{name},
			_far{ far },
			_near{ near },
			_aspect{ aspect },
			_FOV{ FOV },
			_move_speed{ move_speed },
			_rotate_speed{ rotate_speed },
			_ctr{ ctr }
		{
			update();
		}

		virtual bool isInView(const ObjPtr&);
	private:
		mat4 _V;
		mat4 _P;
		CAM_CONTROL_TYPE _ctr;
		float _far, _near;
		float _aspect;
		float _FOV;
		float _move_speed;
		float _rotate_speed;
		string _name;
	};
	typedef shared_ptr<Camera>   CamPtr;
	typedef list<CamPtr>		CamList;
}