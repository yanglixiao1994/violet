#pragma once
#include "RenderSystem.h"
class glRenderSystem :public RenderSystem {
	void setGpuProgram()final override;
	void updateGlobalEnvironmentInfo()final override;
	void bindPerVertexParameters()final override;
	void createWindow(const string&title, uint width, uint height, bool fullscreen)final override;
	void draw()final override;
};