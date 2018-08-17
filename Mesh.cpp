#include "Mesh.h"
#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

//#define USE_ASSIMP
namespace violet {
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
		for (uint32 i = 0; i < scene->mNumMeshes; i++) {
			SubMeshPtr submesh(new SubMesh());
			submesh->_isInGpu = false;
			aiMesh *mesh = scene->mMeshes[i];
			Assert(mesh->mPrimitiveTypes == aiPrimitiveType_TRIANGLE);
			submesh->_primitive = PRIMITIVE_TYPE::Triangle;
			Assert(mesh->HasFaces());
			submesh->_num_vertex_attributes++;
			Assert(mesh->HasNormals());
			submesh->_num_vertex_attributes++;
			Assert(mesh->HasPositions());
			submesh->_num_vertex_attributes++;
			Assert(mesh->HasTextureCoords(0));
			submesh->_num_vertex_attributes++;
			Assert(mesh->GetNumUVChannels() <= 3);
			//Load SubMesh.The default attributes are:position,normal,texcoord[],index.
			for (uint32 j = 0; j < mesh->mNumVertices; j++) {
				submesh->_vertattr3fv[ATTRIBUTE_TYPE::Position].push_back(glm::vec3{ mesh->mVertices[j].x,mesh->mVertices[j].y ,mesh->mVertices[j].z });
				submesh->_vertattr3fv[ATTRIBUTE_TYPE::Normal].push_back(glm::vec3{ mesh->mNormals[j].x,mesh->mNormals[j].y ,mesh->mNormals[j].z });

				//TODO:Load more than one texture coordinates.
				for (uint32 k = 0; k < mesh->GetNumUVChannels(); k++) {
					submesh->_vertattr2fv[ATTRIBUTE_TYPE::Texcoordinate].push_back(glm::vec2{ mesh->mTextureCoords[k][j].x,mesh->mTextureCoords[k][j].y });
					break;
				}
			}

			for (uint32 j = 0; j < mesh->mNumFaces; j++) {
				auto face = mesh->mFaces[j];
				Assert(face.mNumIndices == 3);
				for (int k = 0; k < 3; k++) {
					submesh->_vertattr1iv[ATTRIBUTE_TYPE::Index].push_back(face.mIndices[k]);
				}
			}
			//Load Material
			MatlPtr matlp(new Material());
			aiColor3D ambient;
			aiColor3D diffuse;
			aiColor3D specular;
			aiColor3D emissive;

			scene->mMaterials[mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
			scene->mMaterials[mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
			scene->mMaterials[mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_EMISSIVE, emissive);

			matlp->insertParam3f("diffuse", glm::vec3{ diffuse.r,diffuse.g,diffuse.b });
			matlp->insertParam3f("ambient", glm::vec3{ ambient.r,ambient.g,ambient.b });
			matlp->insertParam3f("emissive", glm::vec3{ emissive.r,emissive.g,emissive.b });

			matlp->setBlendModel(MATL_BLEND_MODEL::Opaque);
			matlp->setCullFace(true);
			matlp->setDepthTest(true);
			matlp->setDepthFunc(DEPTH_FUNCTION::Less);
			matlp->setDiffuseModel(MATL_DIFFUSE_MODEL::Lambert);
			matlp->setShadingModel(MATL_SHADING_MODEL::Phong);
			matlp->setSpecularModel(MATL_SPECULAR_MODEL::Phong);
			matlp->setGpuProgram("phong");
			/*Load Textures*/
			aiString path;
			scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, 0, &path);
			if (path.length == 0) {
				path = "./resource/default.png";
			}

			TexPtr tex{ new Texture{ path.C_Str() } };
			tex->_type = Texture::TEX_TYPE::TextureType_DIFFUSE;
			matlp->_texs.push_back(std::move(tex));

			submesh->_matl = matlp;
			_submeshs.push_back(submesh);
		}
		_file = file;
	}

	void Mesh::clear() {
		_submeshs.clear();
	}

	bool SubMesh::operator <=(const SubMesh&submesh)const {
		return this->_matl <= submesh._matl;
	}


}