#pragma once
#include "auxiliary.h"
class RenderSystem {
public:
	void createWindow(const string&title, uint width, uint height, bool fullscreen);
	void setVertexBuffer(uint numverices, uint attributes);
	void updatePerframe();
	void updatePerObject();
	void render();
};