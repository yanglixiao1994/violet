#include "Scene.h"
namespace violet {

	Scene::Scene():_root(new Object()) {
	}

	void Scene::setCurCam(const string&name) {
		for (const auto&cam : _camList) {
			if (cam->getName() == name) {
				_curCam = cam;
				return;
			}
		}
		Assert(1 == 2);//No Camera
	}

	ObjList Scene::getVisibleObject() {
		ObjList result;
		queue<ObjPtr>temp;
		temp.push(_root);
		for (;temp.size()!=0;) {
			ObjPtr curobj = temp.front();
			if (_curCam->isInView(curobj) && curobj->_mesh.get() != nullptr)
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
		_render->setColor(0, 0, 0);
		RenderQueue renderq;
		for (;;) {
			_render->clear();
			ObjList visiableList = getVisibleObject();
			renderq.clear();
			for (const auto&obj : visiableList) {
				SubMeshVec smv = obj->getSubMesh();
				RenderUnit unit;
				unit._object = obj;
				for (const auto&submesh : smv) {
					unit._submesh = submesh;
					renderq.push_back(unit);
				}
			}
			//renderVec.sort();
			for (const auto&unit : renderq) {
				if (!_render->isInGpu(unit._submesh))_render->uploadSubMesh2Gpu(unit._submesh);
				for (auto &tex : unit._submesh->_matl->_texs)
					if (!_render->isInGpu(tex))_render->uploadTex2Gpu(tex);
				_render->bindSubMesh(unit._submesh);
				_render->bindMaterial(unit._submesh->_matl);
				_render->bindObject(unit._object);
				mat4 MVP = _curCam->getProjMat()*_curCam->getViewMat() *unit._object->getToWorldMat();
				//TODO:use uniform_buffer.
				GlobalEnvironmentInfo info;
				_curCam->update();
				info._curCam = _curCam;
				info._lights = _lightVec;
				_render->bindGlobalEnvironmentInfo(info);
				_render->draw(unit._submesh);
			}
			_render->swapBuffer();
		}
	}
}