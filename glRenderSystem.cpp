#include "glRenderSystem.h"
namespace violet {

	glRenderSystem::glRenderSystem(const WindowInfo&wi) {
		Assert(glfwInit());
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		window = glfwCreateWindow(wi._width, wi._height, wi._title.c_str(), NULL, NULL);
		
		Assert(window);
		glfwMakeContextCurrent(window);
		glewExperimental = GL_TRUE;
		
		Assert(glewInit() == GLEW_OK);
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		loadGpuProgram();
	}

	void glRenderSystem::loadGpuProgram() {
		GpuProgram gprogram;
		gprogram.loadShaders("phong.vertex", "phong.fragment");
		_gpuProgramCache.insert(pair<string, GLuint>("phong", gprogram.id));
	}

	void glRenderSystem::setGpuProgram(const string&gpuName) {
		_curGpuProgram = _gpuProgramCache.at(gpuName);
		glUseProgram(_curGpuProgram);
	}

	void glRenderSystem::bindGlobalEnvironmentInfo(const GlobalEnvironmentInfo&geinfo) {

		//GLuint campos = glGetUniformLocation(_curGpuProgram, "campos");
		//Assert(campos != -1);
		//glUniform3f(campos, geinfo._curCam->getPosition()[0],
		//	geinfo._curCam->getPosition()[1], geinfo._curCam->getPosition()[2]);

		GLuint numLights = glGetUniformLocation(_curGpuProgram, "numlights");
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
				GLuint lightpos = glGetUniformLocation(_curGpuProgram, uniformName.c_str());
				Assert(lightpos != -1);
				glUniform3fv(lightpos, 1, &geinfo._lights[i]->getPosition()[0]);

				ss.clear();
				ss.str("");
				ss << "Lights[" << i << "].color" << ends;
				uniformName = ss.str();
				GLuint lightcolor = glGetUniformLocation(_curGpuProgram, uniformName.c_str());
				Assert(lightcolor != -1);
				glUniform3fv(lightcolor, 1, &geinfo._lights[i]->getColor()[0]);
			}
			++i;
		}
		GLuint V = glGetUniformLocation(_curGpuProgram, "V");
		Assert(V != -1);
		glUniformMatrix4fv(V, 1, GL_FALSE, &geinfo._curCam->getViewMat()[0][0]);
		GLuint P = glGetUniformLocation(_curGpuProgram, "P");
		Assert(P != -1);
		glUniformMatrix4fv(P, 1, GL_FALSE, &geinfo._curCam->getProjMat()[0][0]);
	}
	//TODO:Compare the current matl with the matl,and change the different states.
	void glRenderSystem::bindMaterial(const MatlPtr&mat) {
		if (!_curMatl.get() || mat->_cullface != _curMatl->_cullface) {
			if (mat->_cullface)
				glEnable(GL_CULL_FACE);
			else glDisable(GL_CULL_FACE);
		}

		if (!_curMatl.get() || mat->_depthTest != _curMatl->_depthTest) {
			if(mat->_depthTest)
				glEnable(GL_DEPTH_TEST);
			else glDisable(GL_DEPTH_TEST);
		}

		if (!_curMatl.get() || mat->_depthFunc != _curMatl->_depthFunc) {
			switch (mat->_depthFunc)
			{
			case DEPTH_FUNCTION::Always:glDepthFunc(GL_ALWAYS); break;
			case DEPTH_FUNCTION::Equal:glDepthFunc(GL_EQUAL); break;
			case DEPTH_FUNCTION::Greater:glDepthFunc(GL_GREATER); break;
			case DEPTH_FUNCTION::GreaterEqual:glDepthFunc(GL_GEQUAL); break;
			case DEPTH_FUNCTION::Less:glDepthFunc(GL_LESS); break;
			case DEPTH_FUNCTION::LessEqual:glDepthFunc(GL_LEQUAL); break;
			case DEPTH_FUNCTION::Never:glDepthFunc(GL_NEVER); break;
			case DEPTH_FUNCTION::NotEqual:glDepthFunc(GL_NOTEQUAL); break;
			}
		}
		if(!_curMatl.get() || mat->_gpuProgram != _curMatl->_gpuProgram)setGpuProgram(mat->getGpuProgramName());

		for (const auto &para3 : mat->_param3f) {
			GLuint paramid = glGetUniformLocation(_curGpuProgram, para3.first.c_str());
			Assert(paramid != -1);
			glUniform3f(paramid, para3.second.x, para3.second.y, para3.second.z);
		}

		for (const auto &para2 : mat->_param2f) {
			GLuint paramid = glGetUniformLocation(_curGpuProgram, para2.first.c_str());
			Assert(paramid != -1);
			glUniform2f(paramid, para2.second.x, para2.second.y);
		}

		for (const auto &para1 : mat->_param1f) {
			GLuint paramid = glGetUniformLocation(_curGpuProgram, para1.first.c_str());
			Assert(paramid != -1);
			glUniform1f(paramid, para1.second);
		}
		for (auto &tex : mat->_texs) {
			glBindTexture(GL_TEXTURE_2D, tex->_texId);
			switch (tex->_warping) {
				case Texture::TEX_WARPING_TYPE::Repeat: {
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
					break;
				}
				case Texture::TEX_WARPING_TYPE::MirroredRepeat: {
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
					break;
				}
				case Texture::TEX_WARPING_TYPE::ClampEdge: {
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
					break;
				}
				case Texture::TEX_WARPING_TYPE::ClampBorder: {
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
					break;
				}
			}
			switch (tex->_filter) {
				case Texture::TEX_FILTER_METHOD::Linear: {
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				}
				case Texture::TEX_FILTER_METHOD::Nearest: {
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				}
			}
		}
		_curMatl = mat;
	}

	void glRenderSystem::bindObject(const ObjPtr&obj) {
		GLuint M = glGetUniformLocation(_curGpuProgram, "M");
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
			glGenVertexArrays(1, &submesh->_vaoid);
			glBindVertexArray(submesh->_vaoid);
			for (const auto&p3 : submesh->_vertattr3fv) {
				GpuBufferPtr gbuff = make_unique<glGpuBuffer>();
				gbuff->createBuffer(BUFFER_USAGE::Static, p3.first,
					p3.second.size() * sizeof(vec3), (void*)&(p3.second[0].x));
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

	void glRenderSystem::uploadTex2Gpu(const TexPtr&tex) {
		if (tex->isInGpu())return;
		glGenTextures(1, &tex->_texId);
		glBindTexture(GL_TEXTURE_2D, tex->_texId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->_width, tex->_height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->_dataUint8);
		glGenerateMipmap(GL_TEXTURE_2D);
		tex->_inGpu = true;
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
			mesh->_vertattr1iv[ATTRIBUTE_TYPE::Index].size(), 
			//36,
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
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	}

	bool glRenderSystem::isInGpu(const SubMeshPtr&submesh) {
		if (submesh->_num_vertex_attributes != submesh->_gpubuffers.size())
			return false;
		else return true;
	}

	bool glRenderSystem::isInGpu(const TexPtr&tex) {
		return tex->isInGpu();
	}

}