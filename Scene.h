#include "auxiliary.h"
#include "Object.h"
#include "Camera.h"
#include "Light.h"
#include "RenderSystem.h"


typedef list<CamPtr>  CamList;
typedef list<MatlPtr> MatlList;
typedef list<ObjPtr>  ObjList;
typedef list<LightPtr>LightPtr;

class Scene {
private:
	Object * _root;
	RenderSystem *_render;

	CamPtr _cur_cam;

	MatlList _matls;
	ObjList _objs;

public:
	void insertMatl(const MatlPtr&matl);
	void loadScene(const string&file) {};
	void draw();
};
