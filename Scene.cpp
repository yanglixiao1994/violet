#include "Scene.h"
namespace violet {

	Scene::Scene() :_root{ new Object{}  } {
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

	void Scene::insert(ObjPtr&obj, ObjPtr&parent)
	{
		obj->insertChild(parent);
		if(dynamic_cast<Light*>(obj))
	}

	void Scene::draw() {
		_render->setColor(0, 0, 1);
		SubMeshVec renderVec;
		for (;;) {
			glClear(GL_COLOR_BUFFER_BIT);
			_render->bindGlobalEnvironmentInfo();
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