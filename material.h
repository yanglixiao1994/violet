#pragma once
#include "auxiliary.h"

namespace violet {
	/*We should focus on material in render field.And the material need to know everthing in the world.
	So we put all in the Material file(Such as Lights,Cameras,Objects).*/
	/*The key of Material's parameter should be the same as the uniform variable name in shader.*/
	typedef map<string, glm::vec3>			Param3f;
	typedef map<string, glm::vec2>			Param2f;
	typedef map<string, float>				Param1f;
	typedef map<string, int>				Param1i;
	typedef list<Param3f>					Param3fV;
	typedef list<Param2f>					Param2fV;
	typedef list<Param1f>					Param1fV;
	typedef list<Param1i>					Param1iV;
	class Material;
	typedef shared_ptr<Material> MatlPtr;
	typedef list<MatlPtr> MatlList;

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

	class Texture {
		enum class TEX_FILTER_METHOD {
			Nearest,
			Linear,
		};
		enum class TEX_DATA_TYPE {
			Float,
			Uint8,
		};
		enum class TEX_WARPING_TYPE {
			Repeat,
			MirroredRepeat,
			ClampEdge,
			ClampBorder,
		};
	public:
		Texture(const string&file);
		void loadFile(const string&file);
	private:
		uint8		*	    _dataUint8;
		float		*		_dataFloat;
		int					_width;
		int					_height;
		int					_channels;
		string				_file;
		TEX_DATA_TYPE		_dataType;
		TEX_WARPING_TYPE	_warping;
		TEX_FILTER_METHOD	_filter;
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
			MATL_BLEND_MODEL,
			MATL_SHADING_MODEL,
			MATL_DIFFUSE_MODEL,
			MATL_SPECULAR_MODEL,
			bool cullface,
			bool depthtest,
			DEPTH_FUNCTION depthfunc,
			const string&gpu_program
		);
		Material() {};
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
		vector<Texture>		_texs;
		Param1f				_param1f;
		Param2f				_param2f;
		Param3f				_param3f;
	};
}




