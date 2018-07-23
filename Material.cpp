#include "Material.h"

void Texture::loadFile(const string&file) {
	data_unsigned_char = stbi_load(file.c_str(), &width, &height, &channels, 0);
}
Texture::Texture(const string&file) {
	loadFile(file);
}