#include"Scene.h"
#include"glRenderSystem.h"
using namespace violet;
int main() {
	Scene scene;

	CamPtr cam = make_shared<Camera>(vec3(14,14,13),"walker");
	scene.insert(cam, scene.getRoot());
	scene.setCurCam("walker");

	LightPtr light = make_shared<Light>(vec3(4,4,3),vec3(.7f,0.f,0.f));
	scene.insert(light, scene.getRoot());

	RenderSystem *render = new glRenderSystem(WindowInfo("soft body", 1024, 768, false));
	scene.setRender(render);

	MeshPtr cubeMesh(new Mesh{ "cube.obj" });
	MeshPtr monkeyMesh(new Mesh{ "monkey.obj" });

	ObjPtr cube1(new Object());
	ObjPtr cube2(new Object());
	cube1->setMesh(cubeMesh);
	cube2->setMesh(cubeMesh);
	cube2->move(vec3{ 5.f,0.f,0.f });
	scene.insert(cube1,scene.getRoot());
	scene.insert(cube2, scene.getRoot());

	ObjPtr monkey(new Object(vec3(0,-15,-15)));
	scene.insert(monkey, scene.getRoot());
	monkey->setMesh(monkeyMesh);

	scene.draw();

	return 0;
}