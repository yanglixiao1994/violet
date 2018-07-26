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
struct perObjectInfo {
	Param1f _param1f;
	Param2f _param2f;
	Param3f _param3f;
};
class RenderSystem{
	virtual void setGpuProgram() = 0;
	virtual void updateGlobalEnvironmentInfo(const globalEnvironmentInfo&) = 0;
	virtual void updatePerObjectInfo(const perObjectInfo&) = 0;
	virtual void bindPerVertexAttributes(const submesh&) = 0;
	virtual void createWindow(const string&title, uint width, uint height, bool fullscreen) = 0;
	virtual GpuBufferPtr createGpuBuffer(BUFFER_USAGE, BUFFER_TYPE, uint32 size, void* pSource) = 0;
	virtual void draw() = 0;

};

