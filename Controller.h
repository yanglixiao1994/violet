#pragma once
#include"auxiliary.h"
#include"Component.h"
namespace violet {
	class Controller :public Component{
	public:
		virtual void update() override {};
	};
	class RambleController :public Controller {
		//friend class Object;
	public:
		RambleController(float moveSpeed = 10.f, float rotateSpeed = .001f) :_moveSpeed{ moveSpeed }, _rotateSpeed{ rotateSpeed } {}
		void setMoveSpeed(float speed) {
			_moveSpeed = speed;
		}
		void setRotateSpeed(float speed) {
			_rotateSpeed = speed;
		}
		virtual void update()override final;
	private:
		float _deltaTime;
		float _lastTime;
		float _moveSpeed;
		float _rotateSpeed;
		double _cursorX, _cursorY;
	};
}