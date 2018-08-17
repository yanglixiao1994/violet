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
		MeshPtr			 _dirArrow;
		bool			 _startEditor;
		ObjPtr		  	 _root;
		RenderSystem *	 _render;

		CamPtr			 _curCam;
		CamList			 _camList;
		LightVec		 _lightVec;

		MatlList	     _matls;
		SubMeshList		 _renderList;
		function<void()> _update;
		void drawRenderUnits(const RenderQueue&);
		void drawRenderUnit(const RenderUnit&);
	public:
		Scene(RenderSystem*const rs);
		void	loadScene(const string&file) {};
		ObjPtr  getRoot() {
			return _root;
		}
		void	setCurCam(const string&);
		void	insert(ObjPtr obj, ObjPtr&parent);
		void	draw();
		void	setUpdate(const function<void()>&);
		void	foreachObj(const std::function<void(ObjPtr)>&);
		ObjList	findObjIf(const std::function<bool(ObjPtr)>&);
	};
}
