#pragma once
#include "RenderSystem.h"
#define MAX_LIGHT_NUM 8
class glRenderSystem :public RenderSystem {

	void setGpuProgram()final override;
	void updateGlobalEnvironmentInfo(const globalEnvironmentInfo&)final override;
	void updatePerObjectInfo(const perObjectInfo&)final override;
	void bindPerVertexParameters()final override;
	void createWindow(const string&title, uint width, uint height, bool fullscreen)final override;
	void draw()final override;
private:
	uint				_width;
	uint				_height;
	bool				_fullscreen;
	string				_title;

	GLuint				_cur_gpu_program;
	map<string, GLuint> _gpu_program_cache;
	MatlPtr				_cur_matl;
};