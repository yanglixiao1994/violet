#pragma once
#include "auxiliary.h"
enum class BUFFER_USAGE {
	Static,
	Dynamic
};
//Should be arranged in the order of shader.
enum class BUFFER_TYPE {
	Position,
	Texcoordinate,
	Normal,
	VertexColor,
	Index,
};
class GpuBuffer {
public:
	GpuBuffer():_active(false),_size(0) {};
	virtual ~GpuBuffer() {};
	virtual void createBuffer(BUFFER_USAGE, BUFFER_TYPE, uint32 size, void* pSource) = 0;
	virtual void readData(uint32 offset,uint32 length,void *pDest) = 0;
	virtual void writeData(uint32 offset,uint32 length,void *pDest) = 0;
	virtual void deleteBuffer() = 0;
	uint32 getSize() {
		return _size;
	}
	uint32 getBufferId() {
		return _buffer_id;
	}
	BUFFER_USAGE getBufferUsage() {
		return _usage;
	}
	bool isSystemBuffer() {
		return _inSystemBuffer;
	}
	bool isVideoBuffer() {
		return _inVideoBuffer;
	}
	bool isActive() {
		return _active;
	}

protected:
	bool _active;
	uint32 _size;
	BUFFER_USAGE _usage;
	BUFFER_TYPE _type;
	bool _inSystemBuffer;
	bool _inVideoBuffer;
	uint32 _buffer_id;
};

typedef shared_ptr<GpuBuffer> GpuBufferPtr;
typedef list<GpuBufferPtr> GpuBufferList;

class glGpuBuffer :public GpuBuffer{
	virtual ~glGpuBuffer();
	virtual void createBuffer(BUFFER_USAGE, BUFFER_TYPE, uint32 size, void* pSource)override final;
	virtual void readData(uint32 offset, uint32 length, void *pDest)override final;
	virtual void writeData(uint32 offset, uint32 length, void *pDest)override final;
	virtual void deleteBuffer()override final;
};