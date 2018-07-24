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

class Material {
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
		FLAT,
		GOURAUD,
		PHONG,
	};
	enum MATL_DIFFUSE_MODEL {
		Lambert,
	};
	enum MATL_SPECULAR_MODEL {
		Phong,
		Blinn_Phong,
		Cook_Torrance,
	};
public:
	Material(
		MATL_BLEND_MODEL bm= { MATL_BLEND_MODEL::Opaque},
		MATL_SHADING_MODEL sm= { MATL_SHADING_MODEL::PHONG},
		MATL_DIFFUSE_MODEL dm= { MATL_DIFFUSE_MODEL::Lambert},
		MATL_SPECULAR_MODEL spm= { MATL_SPECULAR_MODEL::Phong},
		bool cullface = {true},
		bool depthtest = {false}
	):blend{bm},shading{sm},diffuse{dm},specular{spm},cullface{cullface},depthtest{depthtest}{};
	Material(const string&file) {};
	//Compare the pariority
	bool operator <=(const Material&);
private:
	MATL_BLEND_MODEL blend;
	MATL_SHADING_MODEL shading;
	MATL_DIFFUSE_MODEL diffuse;
	MATL_SPECULAR_MODEL specular;
	bool cullface;
	bool depthtest;
	vector<Texture>texs;
	map<string, vec3>param_vec3;
	map<string, vec2>param_vec2;
	map<string, float>param_vec1;
};

