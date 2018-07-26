#include "Material.h"

void Texture::loadFile(const std::string&file) {
	_data_uint8 = stbi_load(file.c_str(), &_width, &_height, &_channels, 0);
	_data_type = TEX_DATATYPE::UINT8;
	_file = file;
	_warping = TEX_WARPING_TYPE::Repeat;
	_filter = TEX_FILTER_METHOD::Nearest;
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

void Material::insertParam1f(const string&name, float param) {
	_param1f.insert(std::pair<string, float>(name, param));
}

void Material::insertParam2f(const string&name, const glm::vec2& param) {
	_param2f.insert(std::pair<string, glm::vec2>(name, param));
}

void Material::insertParam3f(const string&name, const glm::vec3& param) {
	_param3f.insert(std::pair<string, glm::vec3>(name, param));
}

float Material::getParam1f(const string&name)const {
	return _param1f.at(name);
}

glm::vec2 Material::getParam2f(const string&name)const {
	return _param2f.at(name);
}

glm::vec3 Material::getParam3f(const string&name)const {
	return _param3f.at(name);
}