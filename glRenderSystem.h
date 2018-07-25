#pragma once
#include "RenderSystem.h"
#include "material.h"

class glRenderSystem :public RenderSystem {
	void setGpuProgram()final override;
	void updateGlobalEnvironmentInfo()final override;
	void updatePerObjectInfo()final override;
	void bindPerVertexParameters()final override;
	void createWindow(const string&title, uint width, uint height, bool fullscreen)final override;
	void draw()final override;
private:
	uint _width;
	uint _height;
	bool _fullscreen;
	string _title;
	map<string, GLuint>_gpu_cache;
	MatlPtr _cur_matl;
};