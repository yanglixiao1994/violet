#include "glRenderSystem.h"
namespace violet {

	glRenderSystem::glRenderSystem(const WindowInfo&wi) {
		Assert(glfwInit());
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		window = glfwCreateWindow(wi._width, wi._height, wi._title.c_str(), NULL, NULL);
		
		Assert(window);
		glfwMakeContextCurrent(window);
		glewExperimental = GL_TRUE;
		
		Assert(glewInit() == GLEW_OK);
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
		glClearColor(0.f, 0.f, .4f, 0.f);
		
		//glEnable(GL_DEPTH_TEST);
		//glDepthFunc(GL_LESS);
		//glEnable(GL_CULL_FACE);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		loadGpuProgram();
	}

	void glRenderSystem::loadGpuProgram() {
		GpuProgram gprogram;
		gprogram.loadShaders("phong.vertex", "phong.fragment");
		_gpu_program_cache.insert(pair<string, GLuint>("phong", gprogram.id));
	}

	void glRenderSystem::setGpuProgram() {
		_cur_gpu_program = _gpu_program_cache[(*_cur_matl).getGpuProgramName()];
		glUseProgram(_cur_gpu_program);
	}

	void glRenderSystem::bindGlobalEnvironmentInfo(const GlobalEnvironmentInfo&geinfo) {

		GLuint campos = glGetUniformLocation(_cur_gpu_program, "camposition");
		Assert(campos != -1);
		glUniform3f(campos, geinfo._cur_cam->getPosition()[0],
			geinfo._cur_cam->getPosition()[1], geinfo._cur_cam->getPosition()[2]);

		GLuint numLights = glGetUniformLocation(_cur_gpu_program, "numlights");
		Assert(numLights != -1);
		glUniform1i(numLights, geinfo._lights.size());
		int i = 0;
		for (const auto &curl : geinfo._lights) {
			if (i >= MAX_LIGHT_NUM)break;
			else {
				ostringstream ss;
				string uniformName;

				ss << "Lights[" << i << "].position" << ends;
				uniformName = ss.str();
				GLuint lightpos = glGetUniformLocation(_cur_gpu_program, uniformName.c_str());
				Assert(lightpos != -1);
				glUniform3fv(lightpos, 1, &geinfo._lights[i]->getPosition()[0]);

				ss.clear();
				ss.str("");
				ss << "Lights[" << i << "].color" << ends;
				uniformName = ss.str();
				GLuint lightcolor = glGetUniformLocation(_cur_gpu_program, uniformName.c_str());
				Assert(lightcolor != -1);
				glUniform3fv(lightcolor, 1, &geinfo._lights[i]->getColor()[0]);
			}
			++i;
		}
		GLuint V = glGetUniformLocation(_cur_gpu_program, "V");
		Assert(V != -1);
		glUniformMatrix4fv(V, 1, GL_FALSE, &geinfo._cur_cam->getViewMat()[0][0]);
		GLuint P = glGetUniformLocation(_cur_gpu_program, "P");
		Assert(P != -1);
		glUniformMatrix4fv(P, 1, GL_FALSE, &geinfo._cur_cam->getProjMat()[0][0]);
	}

	void glRenderSystem::bindMaterial(const MatlPtr&mat) {
		_cur_matl = mat;
		setGpuProgram();
		for (const auto &para3 : mat->_param3f) {
			GLuint paramid = glGetUniformLocation(_cur_gpu_program, para3.first.c_str());
			Assert(paramid != -1);
			glUniform3f(paramid, para3.second.x, para3.second.y, para3.second.z);
		}

		for (const auto &para2 : mat->_param2f) {
			GLuint paramid = glGetUniformLocation(_cur_gpu_program, para2.first.c_str());
			Assert(paramid != -1);
			glUniform2f(paramid, para2.second.x, para2.second.y);
		}

		for (const auto &para1 : mat->_param1f) {
			GLuint paramid = glGetUniformLocation(_cur_gpu_program, para1.first.c_str());
			Assert(paramid != -1);

			glUniform1f(paramid, para1.second);
		}
		//if (mat->_cullface)
		//	glEnable(GL_CULL_FACE);
		//else glDisable(GL_CULL_FACE);
		//if (mat->_depthtest)
		//	glEnable(GL_DEPTH_TEST);
		//else glDisable(GL_DEPTH_TEST);

		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
	}

	void glRenderSystem::bindObject(const ObjPtr&obj) {
		GLuint M = glGetUniformLocation(_cur_gpu_program, "M");
		Assert(M != -1);

		mat4 toWorld = obj->getToWorldMat();
		glUniformMatrix4fv(M, 1, GL_FALSE, &toWorld[0][0]);
	}

	GpuBufferPtr glRenderSystem::createGpuBuffer(BUFFER_USAGE usage, ATTRIBUTE_TYPE type, uint32 size, void* pSource) {
		GpuBufferPtr gbuf(new glGpuBuffer{});
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
		glBindBuffer(gl_type, id);
		glBufferData(gl_type, size, pSource, gl_usage);
		gbuf->setBufferUsage(usage);
		gbuf->setAttributeType(type);
		//_active = true;
		return gbuf;
	}

	void glRenderSystem::uploadSubMesh2Gpu(const SubMeshPtr&submesh) {
		if (!isInGpu(submesh)) {
			submesh->_gpubuffers.clear();
			Assert(submesh->_num_vertex_attributes ==
				submesh->_vertattr1fv.size() + submesh->_vertattr2fv.size() + submesh->_vertattr3fv.size() + submesh->_vertattr1iv.size());
			for (const auto&p3 : submesh->_vertattr3fv) {
				GpuBufferPtr gbuff = make_unique<glGpuBuffer>();
				gbuff->createBuffer(BUFFER_USAGE::Static, p3.first,
					p3.second.size() * sizeof(vec3), (void*)&(p3.second[0].x));
				for (auto x : p3.second) {
					cout << x.x << " " << x.y << " " << x.z << endl;
				}
				submesh->_gpubuffers.push_back(std::move(gbuff));
			}
			for (const auto&p2 : submesh->_vertattr2fv) {
				GpuBufferPtr gbuff = make_unique<glGpuBuffer>();
				gbuff->createBuffer(BUFFER_USAGE::Static, p2.first,
					p2.second.size() * sizeof(vec2), (void*)&(p2.second[0].x));
				submesh->_gpubuffers.push_back(std::move(gbuff));
			}
			for (const auto&p1 : submesh->_vertattr1fv) {
				GpuBufferPtr gbuff = make_unique<glGpuBuffer>();
				gbuff->createBuffer(BUFFER_USAGE::Static, p1.first,
					p1.second.size() * sizeof(float), (void*)&(p1.second[0]));
				submesh->_gpubuffers.push_back(std::move(gbuff));
			}
			for (const auto&p1i : submesh->_vertattr1iv) {
				GpuBufferPtr gbuff = make_unique<glGpuBuffer>();
				gbuff->createBuffer(BUFFER_USAGE::Static, p1i.first,
					p1i.second.size() * sizeof(int), (void*)&(p1i.second[0]));
				submesh->_gpubuffers.push_back(std::move(gbuff));
			}
		}
	}

	void glRenderSystem::bindSubMesh(const SubMeshPtr&submesh) {
		if (!isInGpu(submesh)) {
			submesh->_gpubuffers.clear();
			Assert(submesh->_num_vertex_attributes !=
				submesh->_vertattr1fv.size() + submesh->_vertattr2fv.size() + submesh->_vertattr3fv.size());
			uploadSubMesh2Gpu(submesh);
		}
		int num_attrib = 0;
		for (const auto&gbuff : submesh->_gpubuffers) {
			if (gbuff->getAttributeType() == ATTRIBUTE_TYPE::Index) {
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gbuff->getBufferId());
			}
			else if (is_in(gbuff->getAttributeType(), { ATTRIBUTE_TYPE::Normal,ATTRIBUTE_TYPE::Position,ATTRIBUTE_TYPE::VertexColor })) {
				glBindBuffer(GL_ARRAY_BUFFER, gbuff->getBufferId());
				glEnableVertexAttribArray(num_attrib);
				glVertexAttribPointer(
					num_attrib, 
					3,
					GL_FLOAT, 
					GL_FALSE, 
					0, 
					(void*)0);
				++num_attrib;
			}
			else if (gbuff->getAttributeType() == ATTRIBUTE_TYPE::Texcoordinate) {
				glBindBuffer(GL_ARRAY_BUFFER, gbuff->getBufferId());
				glEnableVertexAttribArray(num_attrib);
				glVertexAttribPointer(
					num_attrib, 
					2, 
					GL_FLOAT, 
					GL_FALSE, 
					0, 
					(void*)0);
				++num_attrib;
			}

		}
	}

	void glRenderSystem::draw(const SubMeshPtr&mesh) {
		glDrawElements(
			GL_TRIANGLES, 
			//mesh->_vertattr1iv[ATTRIBUTE_TYPE::Index].size(), 
			36,
			GL_UNSIGNED_INT, 
			(void*)0);
	}

	void glRenderSystem::swapBuffer() {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void glRenderSystem::setColor(float r, float g, float b) {
		glClearColor(r, g, b, 1);
	}

	void glRenderSystem::clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	bool glRenderSystem::isInGpu(const SubMeshPtr&submesh) {
		if (submesh->_num_vertex_attributes != submesh->_gpubuffers.size())
			return false;
		else return true;
	}

}