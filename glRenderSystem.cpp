#include "glRenderSystem.h"

void glRenderSystem::loadGpuProgram() {
	GpuProgram gprogram;
	gprogram.loadShaders("phong.vertex", "phong.fragment");
	_gpu_program_cache.insert(pair<string, GLuint>("phong", gprogram.id));
}

void glRenderSystem::setGpuProgram() {
	_cur_gpu_program = _gpu_program_cache[(*_cur_matl).getGpuProgramName()];
	glUseProgram(_cur_gpu_program);
}

void glRenderSystem::bindGlobalEnvironmentInfo(const globalEnvironmentInfo&geinfo) {

	GLuint campos = glGetUniformLocation(_cur_gpu_program, "camPosition");
	glUniform3f(campos, geinfo._cur_cam->getPosition()[0], 
		geinfo._cur_cam->getPosition()[1], geinfo._cur_cam->getPosition()[2]);

	GLuint numLights = glGetUniformLocation(_cur_gpu_program, "numLights");
	Assert(numLights != -1);
	glUniform1i(numLights, geinfo._lights.size());
	int i = 0;
	for (const auto &curl:geinfo._lights) {
		if (i >= MAX_LIGHT_NUM)break;
		else {
			ostringstream ss;
			string uniformName;
			ss << "Lights[" << i << "].position" << ends;
			uniformName = ss.str();
			GLuint lightpos = glGetUniformLocation(_cur_gpu_program, uniformName.c_str());
			glUniform3fv(lightpos,1,&geinfo._lights[i]->posi[0]);
			ss.clear();
			ss << "Lights[" << i << "].color" << ends;
			uniformName.clear();
			uniformName = ss.str();
			GLuint lightcolor = glGetUniformLocation(_cur_gpu_program, uniformName.c_str());
			glUniform3fv(lightcolor,1, &geinfo._lights[i]->color[0]);
		}
		++i;
	}
	GLuint V = glGetUniformLocation(_cur_gpu_program, "V");
	glUniformMatrix4fv(V, 1, GL_FALSE, &geinfo._cur_cam->getViewMat()[0][0]);
	GLuint P = glGetUniformLocation(_cur_gpu_program, "P");
	glUniformMatrix4fv(P, 1, GL_FALSE, &geinfo._cur_cam->getProjMat()[0][0]);
}

void glRenderSystem::bindMaterial(const MatlPtr&mat) {
	for (const auto &para3 : mat->_param1fv) {
		GLuint paramid = glGetUniformLocation(_cur_gpu_program, para3.first.c_str());
		glUniform3f(paramid, para3.second.x, para3.second.y, para3.second.z);
	}

	for (const auto &para2 : mat->_param2fv) {
		GLuint paramid = glGetUniformLocation(_cur_gpu_program, para2.first.c_str());
		glUniform2f(paramid, para2.second.x, para2.second.y);
	}

	for (const auto &para1 : mat->_param1fv) {
		GLuint paramid = glGetUniformLocation(_cur_gpu_program, para1.first.c_str());
		glUniform1f(paramid, para1.second);
	}
	if (mat->_cullface)
		glEnable(GL_CULL_FACE);
	else glDisable(GL_CULL_FACE);
	if (mat->_depthtest)
		glEnable(GL_DEPTH_TEST);
	else glDisable(GL_DEPTH_TEST);
	_cur_matl = mat;
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
			gbuff.createBuffer(BUFFER_USAGE::Static,p3.first,
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

void glRenderSystem::bindSubMesh(SubMesh&submesh) {
	if (submesh._num_vertex_attributes != submesh._gpubuffers.size()) {
		submesh._gpubuffers.clear();
		Assert(submesh._num_vertex_attributes !=
			submesh._vertattr1fv.size() + submesh._vertattr2fv.size() + submesh._vertattr3fv.size());
		uploadSubMesh2Gpu(submesh);
	}
	int num_attrib = 0;
	for (const auto&gbuff : submesh._gpubuffers) {
		if (gbuff->getAttributeType() == ATTRIBUTE_TYPE::Index) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gbuff->getBufferId());
			glEnableVertexAttribArray(num_attrib);
			glVertexAttribPointer(num_attrib, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
		}
		else if (gbuff->getAttributeType() == (ATTRIBUTE_TYPE::Normal || ATTRIBUTE_TYPE::Position || ATTRIBUTE_TYPE::VertexColor)) {
			glBindBuffer(GL_ARRAY_BUFFER, gbuff->getBufferId());
			glEnableVertexAttribArray(num_attrib);
			glVertexAttribPointer(num_attrib, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		}
		else if(gbuff->getAttributeType() == ATTRIBUTE_TYPE::Texcoordinate) {
			glBindBuffer(GL_ARRAY_BUFFER, gbuff->getBufferId());
			glEnableVertexAttribArray(num_attrib);
			glVertexAttribPointer(num_attrib, gbuff->getSize() * 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		}
	}
}

void glRenderSystem::createWindow(const windowInfo&wi) {
	Assert(glfwInit());
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(wi._width, wi._height, (wi._title).c_str(), NULL, NULL);

	Assert(window);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	Assert(glewInit() == GLEW_OK);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.f, 0.f, .4f, 0.f);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glDepthFunc(GL_LESS);
}

void glRenderSystem::draw(SubMesh&mesh) {
	if (!mesh._isInGpu)uploadSubMesh2Gpu(mesh);
	bindSubMesh(mesh);
	bindMaterial(mesh._matl);
	setGpuProgram();
}