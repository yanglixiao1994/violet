#pragma once
#include"auxiliary.h"
#include"Component.h"
namespace violet {
	class Controller :public Component{
	public:
		virtual void update() override {};
	};
	class RambleController :public Controller {
	public:
		RambleController(float moveSpeed = 10.f, float lookAroundSpeed = 4.f, 
			float zoomSpeed = .3f, float slideAroundSpeed = .05f);
		
		void setMoveSpeed(float speed) {
			_moveSpeed = speed;
		}
		
		void setLookAroundSpeed(float speed) {
			_lookAroundSpeed = speed;
		}
		
		void setSlideAroundSpeed(float speed) {
			_slideAroundSpeed = speed;
		}
		
		void setZoomAroundSpeed(float speed) {
			_zoomSpeed = speed;
		}
		
		virtual void update()override final;
	
	private:
		float	_deltaTime;
		float	_lastTime;
		float	_lookAroundSpeed;
		float	_slideAroundSpeed;
		float	_zoomSpeed;
		float	_moveSpeed;
		double	_cursorX, _cursorY;
		static double _scrollPos;
	};
}