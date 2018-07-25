#include "glRenderSystem.h"
void glRenderSystem::setGpuProgram() {
	_cur_gpu_program = _gpu_program_cache[(*_cur_matl).getGpuProgramName()];
	glUseProgram(_cur_gpu_program);
}

void glRenderSystem::updateGlobalEnvironmentInfo(const globalEnvironmentInfo&geinfo) {
	int i = 0;
	for (const auto &curl:geinfo._lights) {
		if (i >= MAX_LIGHT_NUM)break;
		else {
			GLuint li_world = glGetUniformLocation(_cur_gpu_program, "li_world");
			glUniform3f(li_world, curl->posi.x, curl->posi.y, curl->posi.z);
			GLuint li_color = glGetUniformLocation(_cur_gpu_program, "li_color");
			glUniform3f(li_color, curl->color.r, curl->color.g, curl->color.b);
		}
		++i;
	}
	GLuint V = glGetUniformLocation(_cur_gpu_program, "V");
	glUniformMatrix4fv(V, 1, GL_FALSE, &geinfo._cur_cam->getViewMat()[0][0]);
	GLuint P = glGetUniformLocation(_cur_gpu_program, "P");
	glUniformMatrix4fv(P, 1, GL_FALSE, &geinfo._cur_cam->getProjMat()[0][0]);

}

void glRenderSystem::updatePerObjectInfo(const perObjectInfo&pobj) {
	for (const auto &para3 : pobj._param3f) {
		GLuint paramid = glGetUniformLocation(_cur_gpu_program, para3.first.c_str());
		glUniform3f(paramid, para3.second.x, para3.second.y, para3.second.z);
	}

	for (const auto &para2 : pobj._param2f) {
		GLuint paramid = glGetUniformLocation(_cur_gpu_program, para2.first.c_str());
		glUniform2f(paramid, para2.second.x, para2.second.y);
	}

	for (const auto &para1 : pobj._param1f) {
		GLuint paramid = glGetUniformLocation(_cur_gpu_program, para1.first.c_str());
		glUniform1f(paramid, para1.second);
	}
}

void glRenderSystem::bindPerVertexParameters() {

}