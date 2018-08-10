#include"Scene.h"
#include"glRenderSystem.h"
using namespace violet;
int main() {
	Scene scene;

	CamPtr cam = make_shared<Camera>(vec3(8,8,8),"walker");
	scene.insert(cam, scene.getRoot());
	scene.setCurCam("walker");

	LightPtr light = make_shared<Light>(vec3(-80,80,80),vec3(.7f,0.f,0.f));
	scene.insert(light, scene.getRoot());
	LightPtr light1 = make_shared<Light>(vec3(80, -80, -80), vec3(0.f, 0.3f, 0.f));
	scene.insert(light1, scene.getRoot());

	RenderSystem *render = new glRenderSystem(WindowInfo("soft body", 1024, 768, false));
	scene.setRender(render);

	MeshPtr cubeMesh(new Mesh{ "cube.obj" });
	MeshPtr monkeyMesh(new Mesh{ "monkeyobj.obj" });

	ObjPtr monkey(new Object());
	scene.insert(monkey, scene.getRoot());
	monkey->setMesh(monkeyMesh);
	monkey->rotate({ 0,50,0 });

	ObjPtr monkey1(new Object());
	scene.insert(monkey1, monkey);
	monkey1->setMesh(monkeyMesh);
	monkey1->move({ 0,2,0 });
	monkey1->rotate({ 0,0,50 });

	scene.draw();

	return 0;
}