#include "glRenderSystem.h"
void glRenderSystem::setGpuProgram() {
	_cur_gpu_program = _gpu_program_cache[(*_cur_matl).getGpuProgramName()];
	glUseProgram(_cur_gpu_program);
}

void glRenderSystem::bindGlobalEnvironmentInfo(const globalEnvironmentInfo&geinfo) {
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

void glRenderSystem::bindMaterial(const Material&mat) {
	for (const auto &para3 : mat._param1fv) {
		GLuint paramid = glGetUniformLocation(_cur_gpu_program, para3.first.c_str());
		glUniform3f(paramid, para3.second.x, para3.second.y, para3.second.z);
	}

	for (const auto &para2 : mat._param2fv) {
		GLuint paramid = glGetUniformLocation(_cur_gpu_program, para2.first.c_str());
		glUniform2f(paramid, para2.second.x, para2.second.y);
	}

	for (const auto &para1 : mat._param1fv) {
		GLuint paramid = glGetUniformLocation(_cur_gpu_program, para1.first.c_str());
		glUniform1f(paramid, para1.second);
	}
}

GpuBufferPtr glRenderSystem::createGpuBuffer(BUFFER_USAGE usage, ATTRIBUTE_TYPE type, uint32 size, void* pSource) {
	GpuBufferPtr gbuf = make_shared<GpuBuffer>(new glGpuBuffer{});
	//if (gbuf->_active)return;
	GLuint id;
	glGenBuffers(1, &id);
	gbuf->setBufferId(id);
	GLenum gl_type, gl_usage;
	switch (usage) {
	case BUFFER_USAGE::Static: {
		gl_usage = GL_STATIC_DRAW;
	}
	case BUFFER_USAGE::Dynamic: {
		gl_usage = GL_DYNAMIC_DRAW;
	}
	}
	if (type == ATTRIBUTE_TYPE::Index) {
		gl_type = GL_ELEMENT_ARRAY_BUFFER;
	}
	else gl_type = GL_ARRAY_BUFFER;
	glBindBuffer(gl_type, 1);
	glBufferData(gl_type, size, pSource, gl_usage);
	gbuf->setBufferUsage(usage);
	gbuf->setAttributeType(type);
	//_active = true;
}

void glRenderSystem::uploadSubMesh2Gpu(SubMesh&submesh) {
	if (submesh._num_vertex_attributes != submesh._gpubuffers.size()) {
		submesh._gpubuffers.clear();
		Assert(submesh._num_vertex_attributes != 
			submesh._vertattr1fv.size() + submesh._vertattr2fv.size() + submesh._vertattr3fv.size());
		for (const auto&p3:submesh._vertattr3fv) {
			glGpuBuffer gbuff;
			gbuff.createBuffer(BUFFER_USAGE::Static, p3.first, 
				p3.second.size() * sizeof(vec3), (void*)&(p3.second[0][0]));
		}
		for (const auto&p2 : submesh._vertattr2fv) {
			glGpuBuffer gbuff;
			gbuff.createBuffer(BUFFER_USAGE::Static, p2.first,
				p2.second.size() * sizeof(vec2), (void*)&(p2.second[0][0]));
		}
		for (const auto&p1 : submesh._vertattr1fv) {
			glGpuBuffer gbuff;
			gbuff.createBuffer(BUFFER_USAGE::Static, p1.first,
				p1.second.size() * sizeof(float), (void*)&(p1));
		}
	}
}

void glRenderSystem::bindSubMesh(const SubMesh&submesh) {
	if (submesh._num_vertex_attributes != submesh._gpubuffers.size()) {
		submesh._gpubuffers.clear();
		Assert(submesh._num_vertex_attributes !=
			submesh._vertattr1fv.size() + submesh._vertattr2fv.size() + submesh._vertattr3fv.size());
}