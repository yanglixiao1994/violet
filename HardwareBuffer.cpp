#include "HardwareBuffer.h"
void HardwareBuffer::createBuffer(BUFFER_USAGE usage, BUFFER_TYPE type, uint32 size, void* pSource) {
	if (_active)return;
	
	glGenBuffers(1, &_buffer_id);
	GLenum _type, _usage;

	switch (usage) {
		case BUFFER_USAGE::Static:{
			_usage = GL_STATIC_DRAW;
		}
		case BUFFER_USAGE::Dynamic: {
			_usage = GL_DYNAMIC_DRAW;
		}
	}
	if (type == BUFFER_TYPE::Index) {
		_type = GL_ARRAY_BUFFER;
	}

	glBindBuffer(_type, 1);
	glBufferData(_type, size, pSource, _usage);
	_active = true;
}

void HardwareBuffer::readData(uint32 offset, uint32 length, void *pDest)
{

}
