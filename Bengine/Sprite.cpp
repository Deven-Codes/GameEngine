#include "Sprite.h"
namespace Bengine {
	Sprite::Sprite()
	{
		_vboID = 0;
	}

	Sprite::~Sprite()
	{
		if (_vboID != 0) {
			glDeleteBuffers(1, &_vboID);
		}
	}

	void Sprite::init(float x, float y, float width, float height, std::string texturePath)
	{
		_x = x;
		_y = y;
		_width = width;
		_height = height;

		//Getting texture of png at filepath if exists in map 
		//else create texture 
		_texture = ResourceManager::getTexture(texturePath);

		if (_vboID == 0) {
			// Generate buffer void glGenBuffers( 	GLsizei n, GLuint* buffers);
			// glGenBuffers — generate buffer object names
			// n - Specifies the number of buffer object names to be generated.
			// buffers - Specifies an array in which the generated buffer object names are stored. 
			glGenBuffers(1, &_vboID);
		}

		Vertex vertexData[6];

		//First Triangle
		vertexData[0].setPosition(x + width, y + height);
		vertexData[0].setUV(1.0f, 1.0f);

		vertexData[1].setPosition(x, y + height);
		vertexData[1].setUV(0.0f, 1.0f);

		vertexData[2].setPosition(x, y);
		vertexData[2].setUV(0.0f, 0.0f);

		//Second Triangle
		vertexData[3].setPosition(x, y);
		vertexData[3].setUV(0.0f, 0.0f);

		vertexData[4].setPosition(x + width, y);
		vertexData[4].setUV(1.0f, 0.0f);

		vertexData[5].setPosition(x + width, y + height);
		vertexData[5].setUV(1.0f, 1.0f);

		for (int i = 0; i < 6; i++) {
			vertexData[i].setColor(255, 255, 255, 255);
		}

		//Bind array buffer to _vboID
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		//Putting vertexData into Buffer
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		//UnBind array buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//Draw sprite to the screen
	void Sprite::draw()
	{
		glBindTexture(GL_TEXTURE_2D, _texture.id);

		//bind the buffer object
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		

		//Draw 6 vertices to the screen
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//Diable the vertex attrib array. This is important
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		//Unbind VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}