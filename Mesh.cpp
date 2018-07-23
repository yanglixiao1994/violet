#include "Mesh.h"
#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

#define USE_ASSIMP
void Mesh::loadMesh(const string&file) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(file,
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType
	);
	if (!scene) {
		cout << file << " has no scene." << endl;
	}
	for (int i = 0; i < scene->mNumMeshes; i++) {
		submesh sm;
		aiMesh *mesh = scene->mMeshes[i];
		for (int j = 0; j < mesh->mNumVertices; j++) {
			sm.vertices.push_back(vec3{ mesh->mVertices[j].x,mesh->mVertices[j].y ,mesh->mVertices[j].z });
			sm.normals.push_back(vec3{ mesh->mNormals[j].x,mesh->mNormals[j].y ,mesh->mNormals[j].z });
			for (int k = 0; k < mesh->GetNumUVChannels; k++) {
				sm.UVs[k].push_back(vec3{ mesh->mTextureCoords[k][j].x,mesh->mTextureCoords[k][j].y,mesh->mTextureCoords[k][j].z });
			}
		}

		shared_ptr<Material>matlp = make_shared<Material>();
		aiColor3D ambient;
		aiColor3D diffuse;
		aiColor3D specular;
		aiColor3D emissive;

		scene->mMaterials[mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
		matlp->param_vec3.insert(pair<string, vec3>{"ambient", vec3{ambient.r,ambient.g,ambient.b}});
		scene->mMaterials[mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_AMBIENT, diffuse);
		matlp->param_vec3.insert(pair<string, vec3>{"diffuse", vec3{ diffuse.r,diffuse.g,diffuse.b }});
		scene->mMaterials[mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_AMBIENT, emissive);
		matlp->param_vec3.insert(pair<string, vec3>{"emissive", vec3{ emissive.r,emissive.g,emissive.b }});
		
		auto texnum = scene->mMaterials[mesh->mMaterialIndex]->GetTextureCount(aiTextureType_DIFFUSE);
		for (int i = 0; i < texnum; i++) {

		}
		sm.matl = matlp;

	}
}