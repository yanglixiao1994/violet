#pragma once
#include "auxiliary.h"
#include "Texture.h"

namespace violet {
	/*We should focus on material in render field.And the material need to know everthing in the world.
	So we put all in the Material file(Such as Lights,Cameras,Objects).*/
	/*The key of Material's parameter should be the same as the uniform variable name in shader.*/

	typedef shared_ptr<class Material>		MatlPtr;
	typedef list<MatlPtr>					MatlList;


	enum class DEPTH_FUNCTION {
		Less,
		Equal,
		LessEqual,
		Greater,
		NotEqual,
		GreaterEqual,
		Always,
		Never,
	};

	enum class MATL_BLEND_MODEL {
		Opaque,
		Masked,
		Translucent,
		Additive,
		Modulate
	};
	enum class MATL_SHADING_MODEL {
		Flat,
		Gouraud,
		Phong,
	};
	enum class MATL_DIFFUSE_MODEL {
		Lambert,
	};

	enum class MATL_SPECULAR_MODEL {
		Phong,
		Blinn_Phong,
		Cook_Torrance,
	};
	enum class MATL_PHYSICAL_MODEL {
		Rigid,
	};
	class Material {
		friend class Mesh;
		friend class Scene;
		//The enum is arranged in the render pariority.
		struct RenderState {
			MATL_BLEND_MODEL	_blend;
			MATL_SHADING_MODEL  _shading;
			MATL_DIFFUSE_MODEL	_diffuse;
			MATL_SPECULAR_MODEL _specular;
			bool				_cullFace;
			bool				_depthTest;
			DEPTH_FUNCTION		_depthFunc;
		};
	public:
		Material(
			MATL_BLEND_MODEL bm = { MATL_BLEND_MODEL::Opaque },
			MATL_SHADING_MODEL sm = { MATL_SHADING_MODEL::Phong },
			MATL_DIFFUSE_MODEL dm = { MATL_DIFFUSE_MODEL::Lambert },
			MATL_SPECULAR_MODEL spm = { MATL_SPECULAR_MODEL::Phong },
			bool cullface = { true },
			bool depthtest = { false },
			DEPTH_FUNCTION depthfunc = { DEPTH_FUNCTION::Less },
			const string&gpu_program = { "Phong" }
		);
		Material(const std::string&) {};
		//Compare the pariority
		bool		operator <=(const Material&)const;
		string		getGpuProgramName()const { return _gpuProgram; }
		void		insertParam3f(const string&name, const glm::vec3&param);
		void		insertParam2f(const string&name, const glm::vec2&param);
		void		insertParam1f(const string&name, float param);
		glm::vec3	getParam3f(const string&name)const;
		glm::vec2	getParam2f(const string&name)const;
		float		getParam1f(const string&name)const;

		MATL_BLEND_MODEL	getBlendModel() { return _blend; }
		MATL_DIFFUSE_MODEL	getDiffuseModel() { return _diffuse; }
		MATL_SHADING_MODEL	getShadingModel() { return _shading; }
		MATL_SPECULAR_MODEL getSpecularModel() { return _specular; }
		bool				isCullFace() { return _cullface; }
		bool				isDepthTest() { return _depthTest; }
		void				setBlendModel(MATL_BLEND_MODEL blend) { _blend = blend; }
		void				setDiffuseModel(MATL_DIFFUSE_MODEL diffuse) { _diffuse = diffuse; }
		void				setSpecularModel(MATL_SPECULAR_MODEL specular) { _specular = specular; }
		void				setShadingModel(MATL_SHADING_MODEL shading) { _shading = shading; }
		void				setCullFace(bool cullface) { _cullface = cullface; }
		void				setDepthTest(bool depthTest) { _depthTest = depthTest; }
		void				setDepthFunc(DEPTH_FUNCTION func) { _depthFunc = func; }
		void				setGpuProgram(const string&gpu_program) { _gpuProgram = gpu_program; }
	private:
		friend class glRenderSystem;
		//Render state
		MATL_BLEND_MODEL	_blend;
		MATL_SHADING_MODEL  _shading;
		MATL_DIFFUSE_MODEL	_diffuse;
		MATL_SPECULAR_MODEL _specular;
		bool				_cullface;
		bool				_depthTest;
		DEPTH_FUNCTION		_depthFunc;
		//
		string				_gpuProgram;
		TexVec				_texs;
		Param1f				_param1f;
		Param2f				_param2f;
		Param3f				_param3f;
	};
}




