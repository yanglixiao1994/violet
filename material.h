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
		UChar,
	};
	enum class TEX_WARPING_TYPE {
		Repeat,
		MirroredRepeat,
		ClampEdge,
		ClampBorder,
	};
	unsigned char*    data_unsigned_char;
	float		 *    data_float;
	int				  width;
	int				  height;
	int				  channels;
	string			  file;
	TEX_DATATYPE      dtype;
	TEX_WARPING_TYPE  warping;
	TEX_FILTER_METHOD filter;
	Texture(const string&file);
	void loadFile(const string&file);
};
typedef map<std::string, vec3> Param3f;
typedef map<std::string, vec2> Param2f;
typedef map<std::string, float> Param1f;
class Material {

	//The enum'order is the render order.
	enum class MATL_PROPERTY {
		Diffuse,
		Specular,
		Ambient,
		Emissive,
	};
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
	string& getGpuProgramName() { return _gpu_program; }
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
