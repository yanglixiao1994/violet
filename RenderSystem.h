#pragma once
#include"auxiliary.h"

class RenderSystem{
	virtual void setGpuProgram() = 0;
	virtual void updateGlobalEnvironmentInfo() = 0;
	virtual void bindPerVertexParameters() = 0;
	virtual void createWindow(const string&title, uint width, uint height, bool fullscreen) = 0;
	virtual void draw() = 0;
};

