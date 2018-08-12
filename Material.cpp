#define STB_IMAGE_IMPLEMENTATION

#include "Material.h"
namespace violet {

	Material::Material(
		MATL_BLEND_MODEL bm,
		MATL_SHADING_MODEL sm,
		MATL_DIFFUSE_MODEL dm,
		MATL_SPECULAR_MODEL spm,
		bool cullface,
		bool depthtest,
		DEPTH_FUNCTION depthfunc,
		const string&gpu_program
	) :_blend{ bm }, _shading{ sm }, _diffuse{ dm }, _specular{ spm },
		_cullface{ cullface }, _depthTest{ depthtest }, _depthFunc{ depthfunc } {};

	bool Material::operator <= (const Material&m)const {
		if (_blend <= m._blend)
			if (_shading <= m._shading)
				if (_diffuse <= m._diffuse)
					if (_specular <= m._specular)
						return true;
		return false;
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
}