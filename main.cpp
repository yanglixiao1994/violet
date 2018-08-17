#include"Scene.h"
#include"glRenderSystem.h"
#include "Controller.h"
using namespace violet;

int main() {

	Scene scene(new glRenderSystem(WindowInfo("soft body", 1280, 1080, false)));

	CamPtr cam = make_shared<Camera>(vec3(5,5,5),"walker");
	CamPtr cam1 = make_shared<Camera>(vec3(5, 5, 5), "test");
	ComPtr control = make_unique<RambleController>();
	cam->addComponent(control);
	scene.insert(cam, scene.getRoot());
	//scene.insert(cam1, dynamic_pointer_cast<Object,Camera>(cam));
	scene.setCurCam("walker");

	LightPtr light = make_shared<Light>(vec3(-80,80,80),vec3(0.7f,0.7f,0.7f));
	scene.insert(light, scene.getRoot());
	LightPtr light1 = make_shared<Light>(vec3(80, -80, -80), vec3(0.f, 0.3f, 0.f));
	//scene.insert(light1, scene.getRoot());


	/*
	MeshPtr houseMesh(new Mesh{ "G:\\model\\house\\house\\house.obj" });
	MeshPtr floorMesh(new Mesh{ "G:\\model\\floor.obj" });
	MeshPtr grassMesh(new Mesh{ "G:\\model\\tree\\tree.obj" });*/
	//MeshPtr carMesh(new Mesh{ "tree.obj" });
	MeshPtr houseMesh(new Mesh{ "house_01.obj" });
	MeshPtr floorMesh(new Mesh{ "untitled.obj" });
	MeshPtr grassMesh(new Mesh{ "./resource/tree/Tree.obj" });
	MeshPtr palmMesh(new Mesh{ "./resource/palm/palm.obj" });

	ObjPtr house(new Object());
	scene.insert(house, scene.getRoot());
	house->setMesh(houseMesh);
	house->rotate({ 0,0,0 });

	ObjPtr floor(new Object());
	scene.insert(floor, house);
	floor->setMesh(floorMesh);
	//monkey1->move({ 0,5,-20 });
	//monkey1->rotate({ 0,0,50 });

	ObjPtr grass(new Object());
	scene.insert(grass, house);
	grass->setMesh(grassMesh);
	grass->move(vec3{ 5.0f,0.f,0.f });

	ObjPtr palm(new Object());
	scene.insert(palm, house);
	palm->setMesh(palmMesh);
	palm->move(vec3{ 5.0f,0.f,5.f });

	//ObjPtr car(new Object());
	//scene.insert(car, house);
	//car->setMesh(carMesh);
	//car->move(vec3{ 5.0f,0.f,0.f });

	scene.setUpdate([&grass,&house]() {
		grass->rotate(vec3{ 0.f, 0.5f, 0.f });
		//house->rotate(vec3{ 0.f, 0.1f, 0.f });
	});

	scene.draw();

	return 0;
}