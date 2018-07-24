#include "Material.h"

void Texture::loadFile(const std::string&file) {
	data_unsigned_char = stbi_load(file.c_str(), &width, &height, &channels, 0);
}
Texture::Texture(const std::string&file) {
	loadFile(file);
}

Material::Material(
	MATL_BLEND_MODEL bm = { MATL_BLEND_MODEL::Opaque },
	MATL_SHADING_MODEL sm = { MATL_SHADING_MODEL::Phong },
	MATL_DIFFUSE_MODEL dm = { MATL_DIFFUSE_MODEL::Lambert },
	MATL_SPECULAR_MODEL spm = { MATL_SPECULAR_MODEL::Phong },
	bool cullface = { true },
	bool depthtest = { false },
	const string&gpu_program = { "Opaque_Phong_Lambert_Phong" }
) :_blend{ bm }, _shading{ sm }, _diffuse{ dm }, _specular{ spm }, _cullface{ cullface }, _depthtest{ depthtest } {};


bool Material::operator <= (const Material&m)const {
	if (_blend <= m._blend)
		if (_shading <= m._shading)
			if (_diffuse <= m._diffuse)
				if (_specular <= m._specular)
					return true;
	else return false;
}