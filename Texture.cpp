#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include "stb_image.h"
namespace violet {
	void Texture::loadFile(const std::string&file) {
		int _channels;
		_dataUint8 = stbi_load(file.c_str(), &_width, &_height, &_channels, 0);
		Assert(_dataUint8 != nullptr);
		switch (_channels) {
			case 1:_format = TEX_FORMAT::R; break;
			case 2:_format = TEX_FORMAT::RG; break;
			case 3:_format = TEX_FORMAT::RGB; break;
			case 4:_format = TEX_FORMAT::RGBA; break;
		}
		_dataType = TEX_DATA_TYPE::Uint8;
		_file = file;
		_warping = TEX_WARPING_TYPE::Repeat;
		_filter = TEX_FILTER_METHOD::Nearest;
	}
	Texture::Texture(const std::string&file) :_inGpu{ false } {
		loadFile(file);
	}
	void Texture::free() {
		stbi_image_free(_dataUint8);
	}

	void Texture::insertParam1f(const string&name, float param) {
		_param1f[name] = param;
	}

	void Texture::insertParam2f(const string&name, const glm::vec2& param) {
		_param2f[name] = param;
	}

	void Texture::insertParam3f(const string&name, const glm::vec3& param) {
		_param3f[name] = param;
	}

	float Texture::getParam1f(const string&name)const {
		return _param1f.at(name);
	}

	glm::vec2 Texture::getParam2f(const string&name)const {
		return _param2f.at(name);
	}

	glm::vec3 Texture::getParam3f(const string&name)const {
		return _param3f.at(name);
	}
}