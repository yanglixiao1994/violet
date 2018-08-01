#include"Scene.h"
#include"glRenderSystem.h"
using namespace violet;
int main() {
	Scene scene;

	CamPtr cam = make_shared<Camera>(vec3(0,0,-10),"walker");
	scene.getRoot()->insertChild(cam);

	LightPtr light = make_shared<Light>();

	RenderSystem *render = new glRenderSystem(windowInfo("soft body", 1024, 768, false));
	scene.setRender(render);

	ObjPtr vegetable(new Object());
	vegetable->loadMesh("cube.obj");
	scene.getRoot()->insertChild(vegetable);

	scene.draw();

	return 0;
}