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
		shared_ptr<SubMesh> sm(new SubMesh());
		sm->_isInGpu = false;
		aiMesh *mesh = scene->mMeshes[i];
		Assert(mesh->mPrimitiveTypes == aiPrimitiveType_TRIANGLE);
		sm->_primitive = PRIMITIVE_TYPE::Triangle;
		Assert(mesh->HasFaces());
		sm->_num_vertex_attributes++;
		Assert(mesh->HasNormals());
		sm->_num_vertex_attributes++;
		Assert(mesh->HasPositions());
		sm->_num_vertex_attributes++;
		Assert(mesh->HasTextureCoords(0));
		sm->_num_vertex_attributes++;
		Assert(mesh->GetNumUVChannels <= 3);
		//Load SubMesh.The default attributes are:position,normal,texcoord[],index.
		for (int j = 0; j < mesh->mNumVertices; j++) {
			sm->_vertattr3fv[ATTRIBUTE_TYPE::Position].push_back(glm::vec3{ mesh->mVertices[j].x,mesh->mVertices[j].y ,mesh->mVertices[j].z });
			sm->_vertattr3fv[ATTRIBUTE_TYPE::Normal].push_back(glm::vec3{ mesh->mNormals[j].x,mesh->mNormals[j].y ,mesh->mNormals[j].z });

			//TODO:Load more than one texture coordinates.
			for (int k = 0; k < mesh->GetNumUVChannels; k++) {
				sm->_vertattr2fv[ATTRIBUTE_TYPE::Texcoordinate].push_back(glm::vec2{ mesh->mTextureCoords[k][j].x,mesh->mTextureCoords[k][j].y});
				break;
			}
		}

		for (int j = 0; j < mesh->mNumFaces; j++) {
			auto face = mesh->mFaces[j];
			Assert(face.mNumIndices == 3);
			for (int k = 0; k < 3; k++) {
				sm->_vertattr1fv[ATTRIBUTE_TYPE::Index].push_back(face.mIndices[k]);
			}
		}
		//Load Material
		shared_ptr<Material>matlp = make_shared<Material>();
		aiColor3D ambient;
		aiColor3D diffuse;
		aiColor3D specular;
		aiColor3D emissive;

		scene->mMaterials[mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
		matlp->insertParam3f.insert(pair<string, glm::vec3>{"ambient", glm::vec3{ambient.r,ambient.g,ambient.b}});
		scene->mMaterials[mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_AMBIENT, diffuse);
		matlp->insertParam3f.insert(pair<string, glm::vec3>{"diffuse", glm::vec3{ diffuse.r,diffuse.g,diffuse.b }});
		scene->mMaterials[mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_AMBIENT, emissive);
		matlp->insertParam3f.insert(pair<string, glm::vec3>{"emissive", glm::vec3{ emissive.r,emissive.g,emissive.b }});
		
		auto texnum = scene->mMaterials[mesh->mMaterialIndex]->GetTextureCount(aiTextureType_DIFFUSE);
		for (int i = 0; i < texnum; i++) {

		}
		sm->_matl = matlp;
		_submeshs.push_back(make_shared<SubMesh>(sm));
	}
}

bool SubMesh::operator <=(const SubMesh&submesh)const {
	return this->_matl <= submesh._matl;
}