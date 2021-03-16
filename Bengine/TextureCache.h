#pragma once
#include <map>
#include <string>
#include "GLTexture.h"
#include "ImageLoader.h"
#include <iostream>

namespace Bengine {
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		GLTexture getTexture(std::string texturePath);

	private:
		std::map<std::string, GLTexture> _textureMap;
	};
}

