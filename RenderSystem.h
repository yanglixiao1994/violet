#pragma once
#include "light.h"
#include "material.h"
#include "Mesh.h"
#include "Light.h"
#include "Camera.h"
#include "GpuBuffer.h"
#include "GpuProgram.h"
struct globalEnvironmentInfo {
	LightVec _lights;
	CamPtr   _cur_cam;
};

struct windowInfo {
	string _title;
	uint32 _width;
	uint32 _height;
	bool _fullscreen;
};


class RenderSystem{
public:
	virtual void setGpuProgram() = 0;
	//Environment,e.g. Lights,Camera.
	virtual void bindGlobalEnvironmentInfo(const globalEnvironmentInfo&) = 0;
	//Different materials have different "BRDF",texture,etc.
	virtual void bindMaterial(const MatlPtr&) = 0;
	//Upload different vertex attributes,e.g. Position,Normal,TexCoord to Gpu Buffer.
	virtual void uploadSubMesh2Gpu(SubMesh&) = 0;
	virtual void bindSubMesh(SubMesh&) = 0;
	virtual void createWindow(const windowInfo&) = 0;
	virtual GpuBufferPtr createGpuBuffer(BUFFER_USAGE, ATTRIBUTE_TYPE,uint32 size, void* pSource) = 0;
	virtual void draw(SubMesh&) = 0;
};

