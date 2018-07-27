#pragma once
#include "light.h"
#include "material.h"
#include "Mesh.h"
#include "Light.h"
#include "Camera.h"
#include "GpuBuffer.h"
struct globalEnvironmentInfo {
	LightList _lights;
	CamPtr   _cur_cam;
};

class RenderSystem{
	virtual void setGpuProgram() = 0;
	//Environment,e.g. Lights,Camera.
	virtual void bindGlobalEnvironmentInfo(const globalEnvironmentInfo&) = 0;
	//Different materials have different "BRDF",texture,etc.
	virtual void bindMaterial(const Material&) = 0;
	//Upload different vertex attributes,e.g. Position,Normal,TexCoord to Gpu Buffer.
	virtual void uploadSubMesh2Gpu(const SubMesh&) = 0;
	virtual void bindSubMesh(const SubMesh&) = 0;
	virtual void createWindow(const string&title, uint width, uint height, bool fullscreen) = 0;
	virtual GpuBufferPtr createGpuBuffer(BUFFER_USAGE, ATTRIBUTE_TYPE, uint32 size, void* pSource) = 0;
	virtual void draw() = 0;

};

