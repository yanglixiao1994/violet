#pragma once
#include "light.h"
#include "Texture.h"
#include "material.h"
#include "Mesh.h"
#include "Camera.h"
#include "GpuBuffer.h"
#include "GpuProgram.h"
namespace violet {
	struct GlobalEnvironmentInfo {
		LightVec _lights;
		CamPtr   _curCam;
	};

	struct WindowInfo {
		string _title;
		uint32 _width;
		uint32 _height;
		bool _fullScreen;
		WindowInfo(const string&title, uint32 width, uint32 height, bool fullscreen) :
			_title(title), _width(width), _height(height), _fullScreen(fullscreen) {};
	};
	/*
	A Scene may have many cameras,but a render system can only have one.
	*/
	class RenderSystem {

	public:
		virtual void setGpuProgram(const string&) = 0;
		//Environment,e.g. Lights,Camera.
		virtual void bindGlobalEnvironmentInfo(const GlobalEnvironmentInfo&) = 0;
		//Different materials have different "BRDF",texture,etc.
		virtual void bindMaterial(const MatlPtr&) = 0;
		virtual void bindTexture(const TexPtr&) = 0;
		//Upload different vertex attributes,e.g. Position,Normal,TexCoord to Gpu Buffer.
		virtual void uploadSubMesh2Gpu(const SubMeshPtr&) = 0;
		virtual void bindSubMesh(const SubMeshPtr&) = 0;
		virtual void bindObject(const ObjPtr&) = 0;
		virtual void uploadTex2Gpu(const TexPtr&) = 0;

		virtual GpuBufferPtr createGpuBuffer(BUFFER_USAGE, ATTRIBUTE_TYPE, uint32 size, void* pSource) = 0;
		virtual void draw(const SubMeshPtr&) = 0;
		virtual void swapBuffer() = 0;
		virtual void setColor(float r, float g, float b) = 0;
		virtual void clear() = 0;
		virtual bool isInGpu(const SubMeshPtr&) = 0;
		virtual bool isInGpu(const TexPtr&) = 0;


	protected:
		DEPTH_FUNCTION _curDepthFunc;
		bool		   _curDepthTest;
		bool		   _curCullFace;
	};

}