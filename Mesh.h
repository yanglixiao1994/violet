#pragma once
#include "auxiliary.h"
#include "Material.h"
#include "GpuBuffer.h"

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
	shared_ptr<Material>	_matl;
	uint8					_num_vertex_attributes;
	PRIMITIVE_TYPE			_primitive;
	GpuBufferList			_gpubuffers;
};
class Mesh {
public:
	Mesh(){};
	void loadMesh(const string&);
private:
	vector<SubMesh>	_submeshs;
};
