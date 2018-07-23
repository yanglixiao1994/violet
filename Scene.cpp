#include "Scene.h"
//TODO:Optimaize the order
void Scene::insertMatl(const Material&matl) {
	//First compare the blend
	for (auto m = matls.begin(); m != matls.end();++m) {
		if (matl.blend <= m->blend)
			if (matl.shading <= m->shading) 
				if (matl.diffuse <= m->diffuse)
					if (matl.specular <= m->specular)
						matls.insert(m,matl);
	}
}