#include "TextureCache.h"

namespace Bengine {
	TextureCache::TextureCache()
	{

	}


	TextureCache::~TextureCache()
	{

	}

	GLTexture TextureCache::getTexture(std::string texturePath)
	{
		//std::map<std::string, GLTexture>::iterator mit = _textureMap.find(texturePath);
		auto mit = _textureMap.find(texturePath); // lookup the texture and see if its in the map

		//check whether texture is present in the map and if not the insert texture
		if (mit == _textureMap.end()) {

			// create texture from the texturePath location 
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

			//make pair of texturepath and newTexture and insert into _textureMap
			_textureMap.insert(std::make_pair(texturePath, newTexture));

			std::cout << "Loaded texture!" << std::endl;
			return newTexture;
		}

		std::cout << "Used Chache texture!" << std::endl;
		return mit->second;
	}
}