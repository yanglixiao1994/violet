#include "auxiliary.h"
#include "Object.h"
#include "Camera.h"
#include "Light.h"
#include "RenderSystem.h"
namespace violet {
	class Scene {
		typedef ObjList RenderQueue;
	private:
		ObjPtr		  	 _root;
		RenderSystem *	 _render;

		CamPtr			 _cur_cam;
		CamList			 _camList;
		LightVec		 _lightVec;

		MatlList	     _matls;
		SubMeshList		 _renderList;

	public:
		Scene();
		void	loadScene(const string&file) {};
		void	setRender(RenderSystem*rs) {
			_render = rs;
		}
		ObjPtr  getRoot() {
			return _root;
		}
		ObjList getVisibleObject();
		void	setCurCam(const string&);
		void	insert(ObjPtr obj, ObjPtr&parent);
		void	draw();
	};
}
