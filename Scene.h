#include "auxiliary.h"
#include "Object.h"
#include "Camera.h"
#include "Light.h"
#include "RenderSystem.h"
namespace violet {
	class Scene {
		typedef ObjList RenderQueue;
	private:
		Object * _root;
		RenderSystem *	 _render;

		CamPtr			 _cur_cam;

		MatlList	     _matls;
		ObjList			 _objs;
		SubMeshList		 _render_list;

	public:
		void insertObj(const ObjPtr &obj, const ObjPtr &father);
		void loadScene(const string&file) {};
		void setRender(RenderSystem*rs) {
			_render = rs;
		}

		ObjList getVisibleObject();
		void draw();
	};
}
