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
struct submesh {
	vector<glm::vec3>_vertices;
	vector<unsigned int>_indices;
	vector<glm::vec3>_normals;
	vector<glm::vec3>_UVs[5];
	Param3vf _param3v;
	Param2vf _param2v;
	Param1vf _param1v;
	shared_ptr<Material>_matl;
	uint8 _num_vertex_attributes;
	PRIMITIVE_TYPE _primitive;
	GpuBufferList  _gpubuffers;
};
class Mesh {
public:
	Mesh(){};
	void loadMesh(const string&);
private:
	vector<submesh>	_submeshs;
};
