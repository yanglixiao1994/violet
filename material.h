#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "auxiliary.h"
#include "stb_image.h"
/*We should focus on material in render field.And the material need to know everthing in the world.
So we put all in the Material file(Such as Lights,Cameras,Objects).*/
/*The key of Material's parameter should be the same as the uniform variable name in shader.*/
class Texture {
	enum class TEX_FILTER_METHOD {
		Nearest,
		Linear,
	};
	enum class TEX_DATATYPE {
		Float,
		UINT8,
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
	uint8		*		_data_uint8;
	float		*		_data_float;
	int					_width;
	int					_height;
	int					_channels;
	string				_file;
	TEX_DATATYPE		_data_type;
	TEX_WARPING_TYPE	_warping;
	TEX_FILTER_METHOD	_filter;
};
class Material {

	//The enum is arranged in the render pariority.
	enum MATL_BLEND_MODEL {
		Opaque,
		Masked,
		Translucent,
		Additive,
		Modulate
	};
	enum MATL_SHADING_MODEL {
		Flat,
		Gouraud,
		Phong,
	};
	enum MATL_DIFFUSE_MODEL {
		Lambert,
	};
	enum MATL_SPECULAR_MODEL {
		Phong,
		Blinn_Phong,
		Cook_Torrance,
	};
	enum MATL_PHYSICAL_MODEL {
		Rigid,
	};
	struct RenderState {
		MATL_BLEND_MODEL	_blend;
		MATL_SHADING_MODEL  _shading;
		MATL_DIFFUSE_MODEL	_diffuse;
		MATL_SPECULAR_MODEL _specular;
		bool				_cullface;
		bool				_depthtest;
	};
public:
	Material(
		MATL_BLEND_MODEL bm = { MATL_BLEND_MODEL::Opaque},
		MATL_SHADING_MODEL sm = { MATL_SHADING_MODEL::Phong},
		MATL_DIFFUSE_MODEL dm = { MATL_DIFFUSE_MODEL::Lambert},
		MATL_SPECULAR_MODEL spm = { MATL_SPECULAR_MODEL::Phong},
		bool cullface = {true},
		bool depthtest = {false},
		const string&gpu_program = {"Opaque_Phong_Lambert_Phong"}
	);
	Material(const std::string&) {};
	//Compare the pariority
	bool		operator <=(const Material&)const;
	string		getGpuProgramName()const { return _gpu_program; }
	void		insertParam3f(const string&name, const glm::vec3&param);
	void		insertParam2f(const string&name, const glm::vec2&param);
	void		insertParam1f(const string&name, float param);
	glm::vec3	getParam3f(const string&name)const;
	glm::vec2	getParam2f(const string&name)const;
	float		getParam1f(const string&name)const;
	Param1fV&	getParam1fV() { return _param1fv; }
	Param2fV&	getParam2fV() { return _param2fv; }
	Param3fV&	getParam3fV() { return _param3fv; }

	MATL_BLEND_MODEL	getBlendModel() { return _blend; }
	MATL_DIFFUSE_MODEL	getDiffuseModel() { return _diffuse; }
	MATL_SHADING_MODEL	getShadingModel() { return _shading; }
	MATL_SPECULAR_MODEL getSpecularModel() { return _specular; }
	bool				isCullFace() { return _cullface; }
	bool				isDepthTest() { return _depthtest; }
	void				setBlendModel(MATL_BLEND_MODEL blend) { _blend = blend; }
	void				setDiffuseModel(MATL_DIFFUSE_MODEL diffuse) { _diffuse = diffuse; }
	void				setSpecularModel(MATL_SPECULAR_MODEL specular) { _specular = specular; }
	void				setShadingModel(MATL_SHADING_MODEL shading) { _shading = shading; }
	void				setCullFace(bool cullface) { _cullface = cullface; }
	void				setDepthTest(bool depthTest) { _depthtest = depthTest; }

private:
	//Render state
	MATL_BLEND_MODEL	_blend;
	MATL_SHADING_MODEL  _shading;
	MATL_DIFFUSE_MODEL	_diffuse;
	MATL_SPECULAR_MODEL _specular;
	bool				_cullface;
	bool				_depthtest;
	//
	string				_gpu_program;
	vector<Texture>		_texs;
	Param1fV			_param1fv;
	Param2fV			_param2fv;
	Param3fV			_param3fv;
};
typedef shared_ptr<Material> MatlPtr;
typedef list<MatlPtr> MatlList;

typedef map<string, glm::vec3>			Param3f;
typedef map<string, glm::vec2>			Param2f;
typedef map<string, float>				Param1f;
typedef map<string, int>				Param1i;
typedef list<Param3f>					Param3fV;
typedef list<Param2f>					Param2fV;
typedef list<Param1f>					Param1fV;
typedef list<Param1i>					Param1iV;


