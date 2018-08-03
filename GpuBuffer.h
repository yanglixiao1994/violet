#pragma once
#include "auxiliary.h"
namespace violet {
	enum class BUFFER_USAGE {
		Static,
		Dynamic
	};
	//Should be arranged in the order of shader.
	enum class ATTRIBUTE_TYPE {
		Position = 0x1,
		Texcoordinate = 0x2,
		Normal = 0x4,
		VertexColor = 0x8,
		Index = 0x10,
	};


	//Vertex Attribute
	typedef map<ATTRIBUTE_TYPE, glm::vec3>			VertAttr3f;
	typedef map<ATTRIBUTE_TYPE, vector<glm::vec3>>	VertAttr3fV;
	typedef map<ATTRIBUTE_TYPE, glm::vec2>			VertAttr2f;
	typedef map<ATTRIBUTE_TYPE, vector<glm::vec2>>	VertAttr2fV;
	typedef map<ATTRIBUTE_TYPE, float>				VertAttr1f;
	typedef map<ATTRIBUTE_TYPE, vector<float>>		VertAttr1fV;

	typedef map<ATTRIBUTE_TYPE, int>				VertAttr1i;
	typedef map<ATTRIBUTE_TYPE, vector<uint32>>		VertAttr1iV;
	class GpuBuffer {
	public:
		GpuBuffer() :_active(false), _size(0) {};
		virtual ~GpuBuffer() {};
		virtual void	createBuffer(BUFFER_USAGE, ATTRIBUTE_TYPE, uint32 sizeinBytes, void* pSource) = 0;
		virtual void	readData(uint32 offset, uint32 length, void *pDest) = 0;
		virtual void	writeData(uint32 offset, uint32 length, void *pDest) = 0;
		virtual void	deleteBuffer() = 0;
		uint32			getSize() {
			return _size;
		}
		uint32			getBufferId() {
			return _buffer_id;
		}
		void			setBufferId(uint32 id) {
			_buffer_id = id;
		}
		BUFFER_USAGE	getBufferUsage() {
			return _usage;
		}
		void			setBufferUsage(BUFFER_USAGE usage) {
			_usage = usage;
		}
		ATTRIBUTE_TYPE  getAttributeType() {
			return _attb_type;
		}
		void			setAttributeType(ATTRIBUTE_TYPE attr) {
			_attb_type = attr;
		}
		bool			isSystemBuffer() {
			return _inSystemBuffer;
		}
		bool			isVideoBuffer() {
			return _inVideoBuffer;
		}
		bool			isActive() {
			return _active;
		}

	protected:
		bool			 _active;
		uint32			 _size;
		BUFFER_USAGE	 _usage;
		ATTRIBUTE_TYPE	 _attb_type;
		bool			 _inSystemBuffer;
		bool			 _inVideoBuffer;
		uint32			 _buffer_id;
	};

	typedef unique_ptr<GpuBuffer>	GpuBufferPtr;
	typedef list<GpuBufferPtr>		GpuBufferList;

	class glGpuBuffer :public GpuBuffer {
	public:
		virtual ~glGpuBuffer();
		virtual void createBuffer(BUFFER_USAGE, ATTRIBUTE_TYPE, uint32 sizeinBytes, void* pSource)override final;
		virtual void readData(uint32 offset, uint32 length, void *pDest)override final;
		virtual void writeData(uint32 offset, uint32 length, void *pDest)override final;
		virtual void deleteBuffer()override final;
	};
}