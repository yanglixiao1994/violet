#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include "stb_image.h"
namespace violet {
	void Texture::loadFile(const std::string&file) {
		_dataUint8 = stbi_load(file.c_str(), &_width, &_height, &_channels, 0);
		Assert(_dataUint8 != nullptr);
		_dataType = TEX_DATA_TYPE::Uint8;
		_file = file;
		_warping = TEX_WARPING_TYPE::Repeat;
		_filter = TEX_FILTER_METHOD::Nearest;
	}
	Texture::Texture(const std::string&file) :_inGpu{ false } {
		loadFile(file);
	}
}