#include "Scene.h"
//TODO:Optimaize the order
void Scene::insertMatl(const Material&matl) {
	//First compare the blend
	for (auto m = matls.begin(); m != matls.end();++m) {
		if (matl <= const_cast<const Material&>(std::move(*m)))
						matls.insert(m,matl);
	}
}