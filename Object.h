#pragma once
#include "auxiliary.h"
#include "Mesh.h"
#include "Component.h"
using namespace glm;
namespace violet {
	/*Objects are the fundamental objects in Violet that represent a node in scene.
	They do not accomplish much in themselves but they act as containers for Components, 
	which implement the real functionality.
	For example, You can control a Object with keyboard by add a control component to the Object.*/
	class Object;
	typedef shared_ptr<Object>  ObjPtr;
	typedef list<ObjPtr> ObjList;
	class Object:public enable_shared_from_this<Object> {
		friend class Scene;
	protected:
		//The relative information to father
		ComList		 _coms;
		vec3		 _posi;
		vec3		 _scaler;
		vec3		 _rotate;
		vec3		 _forward;
		vec3		 _up;
		vec3		 _right;

		list<ObjPtr> _childs;
		ObjPtr       _parent;

		MeshPtr      _mesh;

		bool		 _dirty;
		bool		 _visible;
		bool		 _shadow;
		mat4		 localToParent();
		virtual void setParent(const ObjPtr&obj) {
			_parent = obj;
		}

		virtual void insertChild(const ObjPtr&obj) {
			_childs.push_back(obj);
			obj->setParent(shared_from_this());
		}
	public:
		virtual void update() {
			for (auto &com : _coms) {
				com->update();
			}
		}

		virtual void addComponent(ComPtr&com) {
			com->_owner = shared_from_this();
			_coms.push_back(std::move(com));
		}

		virtual vec3 getForward();

		virtual vec3 getUp();

		virtual vec3 getRight();

		virtual void setMesh(const MeshPtr&mesh) {
			_mesh = mesh;
		}

		virtual void loadMesh(const string&file) {
			if (_mesh.get())_mesh->clear();
			else _mesh = MeshPtr(new Mesh());
			_mesh->loadMesh(file);
		}

		virtual vec3 getPosition() {
			return _posi;
		}

		virtual void reset() {
			_posi = { 0,0,0 };
			_rotate = { 0,0,0 };
			_scaler = { 1,1,1 };
			for (auto &child : _childs) {
				child->reset();
			}
		}

		virtual void scale(const vec3&factor) {
			_scaler += factor;
			for (auto &child : _childs) {
				child->scale(factor);
			}
		}
		//TODO:Get the cpu side euler angle.
		virtual void rotate(float deg, const vec3&axis) {
			//_rotate 
			for (auto &child : _childs) {
				child->rotate(deg, axis);
			}
		}

		virtual void rotate(const vec3&eulerAngle) {
			_rotate += eulerAngle;
		}

		virtual void move(const vec3&step) {
			_posi += step;
			for (auto &child : _childs) {
				child->move(step);
			}
		}

		SubMeshVec getSubMesh() {
			return _mesh->getSubMesh();
		}
		virtual mat4 getToWorldMat();
		//virtual void update();
		Object(
			const vec3&posi = { 0,0,0 },
			const vec3&rotate = {0,0,0},
			const vec3&scaler = {1.f,1.f,1.f},
			Object *parent = nullptr,
			Mesh   *mesh = nullptr,
			bool dirty = true,
			bool visible = true,
			bool throwshadow = true
		) :
			_posi{ posi },
			_rotate{rotate},
			_scaler{scaler},
			_parent{ parent },
			_mesh{ mesh },
			_dirty{ dirty },
			_visible{ visible },
			_shadow{ throwshadow } {};
	};
}

