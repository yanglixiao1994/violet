#pragma once
#include "auxiliary.h"
#include "Mesh.h"
using namespace glm;
namespace violet {
	class Object;
	typedef shared_ptr<Object>  ObjPtr;
	typedef list<ObjPtr> ObjList;
	class Object:enable_shared_from_this<Object> {
		friend class Scene;
	protected:
		//The relative information
		vec3		 _posi;
		vec3		 _scaler;
		vec3		 _rotate;
		mat4		 _toWorld;

		list<ObjPtr> _childs;
		ObjPtr       _parent;

		MeshPtr      _mesh;

		bool		 _dirty;
		bool		 _visible;
		bool		 _shadow;
		mat4		 localToParent();
		void setParent(const ObjPtr&obj) {
			_parent = obj;
		}

		void insertChild(const ObjPtr&obj) {
			_childs.push_back(obj);
			obj->setParent(shared_from_this());
		}
	public:

		void loadMesh(const string&file) {
			if (_mesh.get())_mesh->clear();
			else _mesh = MeshPtr(new Mesh());
			_mesh->loadMesh(file);
		}

		vec3 getPosition() {
			return _posi;
		}

		void reset() {
			_toWorld = mat4(1.f);
			for (auto &child : _childs) {
				child->reset();
			}
		}
		void scale(const vec3&factor) {
			_toWorld = ::scale(_toWorld, factor);
			for (auto &child : _childs) {
				child->scale(factor);
			}
		}
		void rotate(float deg, const vec3&axis) {
			_toWorld = ::rotate(_toWorld, deg / 180.0f, axis);
			for (auto &child : _childs) {
				child->rotate(deg, axis);
			}
		}
		void move(const vec3&step) {
			_toWorld = translate(_toWorld, step);
			for (auto &child : _childs) {
				child->move(step);
			}
		}

		SubMeshVec getSubMesh() {
			return _mesh->getSubMesh();
		}
		mat4 getToWorldMat();
		//virtual void update();

		Object(
			const vec3&posi = vec3{ 0,0,0 },
			Object *parent = nullptr,
			Mesh   *mesh = nullptr,
			bool dirty = true,
			bool visible = true,
			bool throwshadow = true
		) :
			_posi{ posi },
			_parent{ parent },
			_mesh{ mesh },
			_dirty{ dirty },
			_visible{ visible },
			_shadow{ throwshadow } {};


	};
}

