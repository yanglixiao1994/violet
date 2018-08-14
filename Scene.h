#include "auxiliary.h"
#include "Object.h"
#include "Camera.h"
#include "Light.h"
#include "Texture.h"
#include "RenderSystem.h"
namespace violet {
	class Scene {
		struct RenderUnit {
			SubMeshPtr _submesh;
			ObjPtr     _object;
		};
		using RenderQueue = vector<RenderUnit>;
	private:
		ObjPtr		  	 _root;
		RenderSystem *	 _render;

		CamPtr			 _curCam;
		CamList			 _camList;
		LightVec		 _lightVec;

		MatlList	     _matls;
		SubMeshList		 _renderList;
		function<void()> _update;
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
		void	setUpdate(const function<void()>&);
	};
}
