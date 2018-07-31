#include "Scene.h"
namespace violet {
	//TODO:Optimaize the order
	void Scene::insertObj(const ObjPtr&obj, const ObjPtr&parent) {
		//First compare the blend
		parent->insertChild(obj);
		obj->setParent(parent);
	}

	ObjList Scene::getVisibleObject() {
		ObjList result;
		for (auto &obj : _objs) {
			if (_cur_cam->isInView(obj))
				result.push_back(obj);
		}
		return result;
	}

	void Scene::draw() {

		for (;;) {
			float tmp = rand() % 10;
			_render->setColor(tmp / 10.f, 1.f, 0.f);
			_render->swapBuffer();


			glClear(GL_COLOR_BUFFER_BIT);
			ObjList visiableList = getVisibleObject();
			SubMeshList renderList;
			for (const auto&obj : renderList) {
				renderList.push_back(obj);
			}
			renderList.sort();
		}
	}
}