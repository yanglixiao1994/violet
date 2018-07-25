#pragma once
#include "auxiliary.h"
enum class BUFFER_USAGE {
	Static,
	Dynamic
};
enum class BUFFER_TYPE {
	Position,
	Normal,
	VertexColor,
	Texcoordinate,
	Index,
};
class HardwareBuffer {
public:
	HardwareBuffer() {};
	~HardwareBuffer();
	void createBuffer(BUFFER_USAGE, BUFFER_TYPE, uint32 size, void* pSource);
	void readData(uint32 offset,uint32 length,void *pDest);
	void writeData(uint32 offset,uint32 length,void *pDest);
	uint32 getSize() {
		return _size;
	}
	uint32 getBufferId() {
		return _buffer_id;
	}
	BUFFER_USAGE getBufferUsage() {
		return _usage;
	}
	bool isInSystemBuffer() {
		return _inSystemBuffer;
	}
	bool isInVideoBuffer() {
		return _inVideoBuffer;
	}
	void deleteBuffer();
private:
	bool _active;
	uint32 _size;
	BUFFER_USAGE _usage;
	bool _inSystemBuffer;
	bool _inVideoBuffer;
	uint32 _buffer_id;
};