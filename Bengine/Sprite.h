#pragma once

//#include<GL/glew.h> //already included in "Vertex.h"
#include "Vertex.h"
#include <cstddef> // used for offsetof()
#include "GLTexture.h"
#include <string>
#include "ResourceManager.h"


namespace Bengine {
	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void init(float x, float y, float width, float height, std::string texturePath);

		void draw();

	private:
		float _x;
		float _y;
		float _width;
		float _height;
		GLuint _vboID;
		GLTexture _texture;

	};

}