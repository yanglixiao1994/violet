#include "GpuBuffer.h"
namespace violet {
	glGpuBuffer::~glGpuBuffer() {
		deleteBuffer();
	}

	void glGpuBuffer::deleteBuffer() {
		if (!_active)
			glDeleteBuffers(_size, &_bufferId);
	}

	void glGpuBuffer::createBuffer(BUFFER_USAGE usage, ATTRIBUTE_TYPE type, uint32 size, void* pSource) {
		if (_active)return;

		glGenBuffers(1, &_bufferId);
		GLenum gl_type, gl_usage;

		switch (usage) {
		case BUFFER_USAGE::Static: {
			gl_usage = GL_STATIC_DRAW;
			break;
		}
		case BUFFER_USAGE::Dynamic: {
			gl_usage = GL_DYNAMIC_DRAW;
			break;
		}
		}
		if (type == ATTRIBUTE_TYPE::Index) {
			gl_type = GL_ELEMENT_ARRAY_BUFFER;
		}
		else gl_type = GL_ARRAY_BUFFER;
		glBindBuffer(gl_type, _bufferId);
		if (type == ATTRIBUTE_TYPE::Position) {
			static const GLfloat g_vertex_buffer_data[] = {
				-1.0f,-1.0f,-1.0f,
				-1.0f,-1.0f, 1.0f,
				-1.0f, 1.0f, 1.0f,
				1.0f, 1.0f,-1.0f,
				-1.0f,-1.0f,-1.0f,
				-1.0f, 1.0f,-1.0f,
				1.0f,-1.0f, 1.0f,
				-1.0f,-1.0f,-1.0f,
				1.0f,-1.0f,-1.0f,
				1.0f, 1.0f,-1.0f,
				1.0f,-1.0f,-1.0f,
				-1.0f,-1.0f,-1.0f,
				-1.0f,-1.0f,-1.0f,
				-1.0f, 1.0f, 1.0f,
				-1.0f, 1.0f,-1.0f,
				1.0f,-1.0f, 1.0f,
				-1.0f,-1.0f, 1.0f,
				-1.0f,-1.0f,-1.0f,
				-1.0f, 1.0f, 1.0f,
				-1.0f,-1.0f, 1.0f,
				1.0f,-1.0f, 1.0f,
				1.0f, 1.0f, 1.0f,
				1.0f,-1.0f,-1.0f,
				1.0f, 1.0f,-1.0f,
				1.0f,-1.0f,-1.0f,
				1.0f, 1.0f, 1.0f,
				1.0f,-1.0f, 1.0f,
				1.0f, 1.0f, 1.0f,
				1.0f, 1.0f,-1.0f,
				-1.0f, 1.0f,-1.0f,
				1.0f, 1.0f, 1.0f,
				-1.0f, 1.0f,-1.0f,
				-1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f,
				-1.0f, 1.0f, 1.0f,
				1.0f,-1.0f, 1.0f
			};
			//glBufferData(gl_type, size, pSource, gl_usage);
			glBufferData(gl_type, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, gl_usage);
		}
		glBufferData(gl_type, size, pSource, gl_usage);
		//if (type == ATTRIBUTE_TYPE::Position) {
		//	cout << "GPUBUFF---------------------" << endl;
		//	for (int i = 0; i < size/4; i++) {
		//		if (i % 3 == 0)cout << endl;
		//		cout << (float)*((float*)pSource + i) << " ";
		//	}
		//	cout << "GPUBUFF---------------------" << endl;
		//}

		_usage = usage;
		_attbType = type;
		_active = true;
	}

	void glGpuBuffer::readData(uint32 offset, uint32 length, void *pDest)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
		GLenum gl_type;
		if (_attbType != ATTRIBUTE_TYPE::Index) {
			gl_type = GL_ARRAY_BUFFER;
		}
		else gl_type = GL_ELEMENT_ARRAY_BUFFER;
		glGetBufferSubData(gl_type, offset, length, pDest);
	}

	void glGpuBuffer::writeData(uint32 offset, uint32 length, void *pDest)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
		GLenum gl_type;
		if (_attbType != ATTRIBUTE_TYPE::Index) {
			gl_type = GL_ARRAY_BUFFER;
		}
		else gl_type = GL_ELEMENT_ARRAY_BUFFER;
		glBufferSubData(gl_type, offset, length, pDest);
	}
}