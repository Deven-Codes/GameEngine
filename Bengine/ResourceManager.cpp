#include "ResourceManager.h"

namespace Bengine {
	//Static variables needs to be declared inside .cpp file as well
	TextureCache ResourceManager::_textureCache;


	GLTexture ResourceManager::getTexture(std::string texturePath)
	{
		return _textureCache.getTexture(texturePath);
	}
}