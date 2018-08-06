#include"Scene.h"
#include"glRenderSystem.h"
using namespace violet;
int main() {
	Scene scene;

	CamPtr cam = make_shared<Camera>(vec3(-10,0,0),"walker");
	scene.insert(cam, scene.getRoot());
	scene.setCurCam("walker");

	LightPtr light = make_shared<Light>(vec3(1,1,1));
	scene.insert(light, scene.getRoot());

	RenderSystem *render = new glRenderSystem(WindowInfo("soft body", 1024, 768, false));
	scene.setRender(render);

	ObjPtr vegetable(new Object());
	vegetable->loadMesh("cube.obj");
	scene.insert(vegetable,scene.getRoot());

	scene.draw();

	return 0;
}