#pragma once
#include"auxiliary.h"
#include"Material.h"
class Mesh {
	struct submesh {
		vector<vec3>vertices;
		vector<unsigned int>indices;
		vector<vec3>normals;
		vector<vec3>UVs[5];
		map<string, vector<vec3>>mesh_param_vec3;
		map<string, vector<vec2>>mesh_param_vec2;
		map<string, vector<float>>mesh_param_vec1;
		shared_ptr<Material>matl;
	};
public:
	void loadMesh(const string&);
private:
	vector<submesh>submeshs;
};
