#pragma once
#include "light.h"
#include "material.h"
#include "Mesh.h"
#include "Camera.h"
#include "GpuBuffer.h"
#include "GpuProgram.h"
namespace violet {
	struct GlobalEnvironmentInfo {
		LightVec _lights;
		CamPtr   _cur_cam;
	};

	struct WindowInfo {
		string _title;
		uint32 _width;
		uint32 _height;
		bool _fullscreen;
		WindowInfo(const string&title, uint32 width, uint32 height, bool fullscreen) :
			_title(title), _width(width), _height(height), _fullscreen(fullscreen) {};
	};
	/*
	A Scene may have many cameras,but a render system can only have one.
	*/
	class RenderSystem {
	public:
		virtual void setGpuProgram() = 0;
		//Environment,e.g. Lights,Camera.
		virtual void bindGlobalEnvironmentInfo(const GlobalEnvironmentInfo&) = 0;
		//Different materials have different "BRDF",texture,etc.
		virtual void bindMaterial(const MatlPtr&) = 0;
		//Upload different vertex attributes,e.g. Position,Normal,TexCoord to Gpu Buffer.
		virtual void uploadSubMesh2Gpu(const SubMeshPtr&) = 0;
		virtual void bindSubMesh(const SubMeshPtr&) = 0;
		virtual void bindObject(const ObjPtr&) = 0;

		virtual GpuBufferPtr createGpuBuffer(BUFFER_USAGE, ATTRIBUTE_TYPE, uint32 size, void* pSource) = 0;
		virtual void draw(const SubMeshPtr&) = 0;
		virtual void swapBuffer() = 0;
		virtual void setColor(float r, float g, float b) = 0;
		virtual void clear() = 0;
		virtual bool isInGpu(const SubMeshPtr&) = 0;
	};

}