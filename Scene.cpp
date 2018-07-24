#include "Scene.h"
//TODO:Optimaize the order
void Scene::insertMatl(const MatlPtr&matl){
	//First compare the blend
	for (auto m = _matls.begin(); m != _matls.end();++m) {
		if (*matl <= *(*m))
			_matls.insert(m,matl);
	}
}

void Scene::draw() {
	for (auto&mat : _matls) {

	}
}