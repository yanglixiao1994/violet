#pragma once
#include "auxiliary.h"
namespace violet {
	class Component {
		friend class Object;
	public:
		virtual void update() = 0;
	protected:
		using ObjPtr = shared_ptr<class Object>;
		ObjPtr _owner;
	};
	using ComPtr = unique_ptr<Component>;
	using ComList = list<ComPtr>;
}