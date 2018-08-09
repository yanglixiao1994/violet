#pragma once
#include "Object.h"
namespace violet {
	class Component {
		virtual void update() = 0;
	protected:
		ObjPtr _owner;
	};
}