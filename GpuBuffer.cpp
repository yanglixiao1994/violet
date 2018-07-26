#include "GpuBuffer.h"

glGpuBuffer::~glGpuBuffer() {
	deleteBuffer();
}

void glGpuBuffer::deleteBuffer() {
	if (!_active)
		glDeleteBuffers(_size, &_buffer_id);
}

void glGpuBuffer::createBuffer(BUFFER_USAGE usage, BUFFER_TYPE type, uint32 size, void* pSource) {
	if (_active)return;
	
	glGenBuffers(1, &_buffer_id);
	GLenum gl_type,gl_usage;

	switch (usage) {
		case BUFFER_USAGE::Static:{
			gl_usage = GL_STATIC_DRAW;
		}
		case BUFFER_USAGE::Dynamic: {
			gl_usage = GL_DYNAMIC_DRAW;
		}
	}
	if (type == BUFFER_TYPE::Index) {
		gl_type = GL_ELEMENT_ARRAY_BUFFER;
	}
	else gl_type = GL_ARRAY_BUFFER;
	glBindBuffer(gl_type, 1);
	glBufferData(gl_type, size, pSource, gl_usage);
	_usage = usage;
	_type = type;
	_active = true;
}

void glGpuBuffer::readData(uint32 offset, uint32 length, void *pDest)
{
	glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);
	GLenum gl_type;
	if (_type != BUFFER_TYPE::Index) {
		gl_type = GL_ARRAY_BUFFER;
	}
	else gl_type = GL_ELEMENT_ARRAY_BUFFER;
	glGetBufferSubData(gl_type, offset, length, pDest);
}

void glGpuBuffer::writeData(uint32 offset, uint32 length, void *pDest)
{
	glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);
	GLenum gl_type;
	if (_type != BUFFER_TYPE::Index) {
		gl_type = GL_ARRAY_BUFFER;
	}
	else gl_type = GL_ELEMENT_ARRAY_BUFFER;
	glBufferSubData(gl_type, offset, length, pDest);
}