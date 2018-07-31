#include"Scene.h"
#include"glRenderSystem.h"
using namespace violet;
int main() {
	Scene scene;
	windowInfo wi("soft body", 1024, 768, false);
	RenderSystem *render = new glRenderSystem(wi);
	scene.setRender(render);
	scene.draw();
	return 0;
}