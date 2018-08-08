#pragma once
#include "auxiliary.h"
#include "Material.h"
#include "GpuBuffer.h"

namespace violet {
	enum class PRIMITIVE_TYPE {
		Point,
		Line,
		Line_Strip,
		Triangle,
		Triangle_strip,
		Triangle_fan
	};
	typedef map<ATTRIBUTE_TYPE, vector<int>> Paramv1i;
	struct SubMesh {
		VertAttr3fV				_vertattr3fv;
		VertAttr2fV				_vertattr2fv;
		VertAttr1fV				_vertattr1fv;
		VertAttr1iV				_vertattr1iv;
		MatlPtr					_matl;
		uint8					_num_vertex_attributes;
		PRIMITIVE_TYPE			_primitive;
		GpuBufferList			_gpubuffers;
		uint32					_gpuid;
		uint32					_vaoid;
		bool					_isInGpu;
		bool operator <=(const SubMesh&)const;
	};
	typedef shared_ptr<SubMesh> SubMeshPtr;
	typedef vector<SubMeshPtr> SubMeshVec;
	typedef list<SubMeshPtr> SubMeshList;

	class Mesh {
	public:
		Mesh() {};
		Mesh(const string&file) {
			loadMesh(file);
		}
		void loadMesh(const string&);
		void clear();
		SubMeshVec getSubMesh() {
			return _submeshs;
		}
	private:
		SubMeshVec	_submeshs;
		string      _file;
	};
	using MeshPtr = shared_ptr<Mesh>;
}