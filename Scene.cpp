#include "Scene.h"
//TODO:Optimaize the order
void Scene::insertObj(const ObjPtr&obj,const ObjPtr&father){
	//First compare the blend
	father->insertChild(obj);
	obj->setFather(father);
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
	ObjList visiableList = getVisibleObject();
	SubMeshList renderList;
	for (const auto&obj : renderList) {
		renderList.push_back(obj);
	}
	renderList.sort();
}