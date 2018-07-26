#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "auxiliary.h"
#include "stb_image.h"
/*We should focus on material in render field.And the material need to know everthing in the world.
So we put all in the Material file(Such as Lights,Cameras,Objects).*/
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
	bool operator <=(const Material&)const;
	string getGpuProgramName()const { return _gpu_program; }
	void insertParam3f(const string&name, const glm::vec3&param);
	void insertParam2f(const string&name, const glm::vec2&param);
	void insertParam1f(const string&name, float param);
	glm::vec3 getParam3f(const string&name)const;
	glm::vec2 getParam2f(const string&name)const;
	float getParam1f(const string&name)const;

private:
	string				_gpu_program;
	MATL_BLEND_MODEL	_blend;
	MATL_SHADING_MODEL  _shading;
	MATL_DIFFUSE_MODEL	_diffuse;
	MATL_SPECULAR_MODEL _specular;
	bool				_cullface;
	bool				_depthtest;
	vector<Texture>		_texs;
	Param1f				_param1f;
	Param2f				_param2f;
	Param3f				_param3f;
};
typedef shared_ptr<Material> MatlPtr;
typedef list<MatlPtr> MatlList;
