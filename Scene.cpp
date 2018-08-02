#include "Scene.h"
namespace violet {

	Scene::Scene():_root(new Object()) {
	}

	void Scene::setCurCam(const string&name) {
		for (const auto&cam : _camList) {
			if (cam->getName() == name) {
				_cur_cam = cam;
				return;
			}
		}
		Assert(1 == 2);
	}

	ObjList Scene::getVisibleObject() {
		ObjList result;
		queue<ObjPtr>temp;
		temp.push(_root);
		for (;temp.size()!=0;) {
			ObjPtr curobj = temp.front();
			if (_cur_cam->isInView(curobj))
				result.push_back(curobj);
			for (const auto&child : curobj->_childs) {
				temp.push(child);
			}
			temp.pop();
		}
		return result;
	}

	void Scene::insert(ObjPtr obj, ObjPtr&parent)
	{
		parent->insertChild(obj);
		LightPtr ptr = dynamic_pointer_cast<Light>(obj);
		if (ptr != nullptr) {
			_lightVec.push_back(ptr);
			return;
		}
		CamPtr ptr1 = dynamic_pointer_cast<Camera>(obj);
		if (ptr1 != nullptr) {
			_camList.push_back(ptr1);
			return;
		}
	}

	void Scene::draw() {
		_render->setColor(0, 0, 1);
		SubMeshVec renderVec;
		for (;;) {
			glClear(GL_COLOR_BUFFER_BIT);
			globalEnvironmentInfo info;
			info._cur_cam = _cur_cam;
			info._lights = _lightVec;
			_render->bindGlobalEnvironmentInfo(info);
			ObjList visiableList = getVisibleObject();
			for (const auto&obj : visiableList) {
				SubMeshVec smv = obj->getSubMesh();
				for(const auto&submesh:smv)
					renderVec.push_back(submesh);
			}
			//renderVec.sort();
			for (const auto&submesh : renderVec) {
				_render->draw(submesh);
			}
			_render->swapBuffer();
		}
	}
}