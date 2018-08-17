#include "Scene.h"
namespace violet {

	Scene::Scene(RenderSystem*const rs) :_render{ rs },_root(new Object()), 
		_dirArrow(new Mesh{ "./resource/arrow.obj" }){
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

	void Scene::drawRenderUnits(const RenderQueue&renderq){
		for (const auto&unit : renderq) {
			if (!_render->isInGpu(unit._submesh))_render->uploadSubMesh2Gpu(unit._submesh);
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
	}

	void Scene::drawRenderUnit(const RenderUnit&unit) {
		if (!_render->isInGpu(unit._submesh))_render->uploadSubMesh2Gpu(unit._submesh);

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

	void Scene::draw() {
		static bool firstTime = true;
		_render->setColor(0, 0, 0);
		RenderQueue renderq;
		for (;;) {
			_update();
			/*Push Visible SubMesh into RenderQueue*/
			_render->clear();
			ObjList visiableList = findObjIf([this](const ObjPtr&obj)->bool {
				if (_curCam->isInView(obj))
					return true;
				else return false;
			});
			renderq.clear();
			for (const auto&obj : visiableList) {
				if (obj->_mesh.get() == nullptr)continue;
				SubMeshVec smv = obj->getSubMesh();
				RenderUnit unit;
				unit._object = obj;
				for (const auto&submesh : smv) {
					unit._submesh = submesh;
					renderq.push_back(unit);
				}
			}
			/*Draw Visible SubMeshs in Least-Change render states*/
			drawRenderUnits(renderq);
			/*Draw things only Editor need*/
			if (_startEditor) {
				/*Push direction arrows(red for forward,green for up,blue for right)into RenderQueue*/
				for (const auto &obj : visiableList) {
					ObjPtr redArrow(new Object{}), greenArrow(new Object{}), blueArrow(new Object{});
					redArrow->_posi = greenArrow->_posi = blueArrow->_posi = vec3{0,0,0};
					redArrow->setParent(obj);
					greenArrow->setParent(obj);
					blueArrow->setParent(obj);
					redArrow->_rotate = obj->_rotate;
					greenArrow->_rotate = obj->_rotate + vec3{90,0,0};
					blueArrow->_rotate = obj->_rotate + vec3{0,90,0};
					redArrow->setMesh(_dirArrow);
					greenArrow->setMesh(_dirArrow);
					blueArrow->setMesh(_dirArrow);

					RenderUnit unit;
					for (const auto&submesh :_dirArrow->getSubMesh()) {
						for (int i = 0; i < 3; i++) {
							submesh->_matl->setDepthTest(false);
							switch (i) {
								case 0: {
									submesh->_matl->insertParam3f("emissive", vec3{ 1.0f,0.f,0.f });
									submesh->_matl->insertParam3f("diffuse", vec3{ 0.0f,0.f,0.f });
									unit._object = redArrow;
									break;
								}
								case 1: {
									submesh->_matl->insertParam3f("emissive", vec3{ 0.f,1.f,0.f });
									submesh->_matl->insertParam3f("diffuse", vec3{ 0.0f,0.f,0.f });
									unit._object = greenArrow;
									break;
								}
								case 2: {
									submesh->_matl->insertParam3f("emissive", vec3{ 0.f,0.f,1.f });
									submesh->_matl->insertParam3f("diffuse", vec3{ 0.0f,0.f,0.f });
									unit._object = blueArrow;
									break;
								}
							}
							unit._submesh = submesh;
							drawRenderUnit(unit);
						}
					}
				}
			}
			_render->swapBuffer();
			//if (firstTime) {
			//	firstTime = false;
			//	foreachObj([](const ObjPtr&obj) {
			//		if (obj->getMesh().get() != nullptr) {
			//			obj->getMesh()->clear();
			//		}
			//	});
			//}
		}
	}
	
	void Scene::foreachObj(const function<void(ObjPtr)>&func) {
		queue<ObjPtr>temp;
		temp.push(_root);
		for (; temp.size() != 0;) {
			ObjPtr curobj = temp.front();
			curobj->update();
			func(curobj);
			for (const auto&child : curobj->_childs) {
				temp.push(child);
			}
			temp.pop();
		}
	}

	ObjList Scene::findObjIf(const function<bool(ObjPtr)>&predicate) {
		ObjList result;
		queue<ObjPtr>temp;
		temp.push(_root);
		for (; temp.size() != 0;) {
			ObjPtr curobj = temp.front();
			curobj->update();
			if(predicate(curobj))
				result.push_back(curobj);
			for (const auto&child : curobj->_childs) {
				temp.push(child);
			}
			temp.pop();
		}
		return result;
	}

	void Scene::setUpdate(const function<void()>&func) {
		_update = func;
	}
}