#include "glRenderSystem.h"
void glRenderSystem::setGpuProgram() {
	glUseProgram(_gpu_cache[(*_cur_matl).getGpuProgramName()]);
}

void glRenderSystem::updateGlobalEnvironmentInfo() {

}