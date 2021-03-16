#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <algorithm>
#include "Vertex.h"

namespace Bengine {

	enum class GlyphSortType {
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	struct Glyph {
		GLuint texture;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
	};

	class RenderBatch {
	public:
		RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture): offset(Offset), 
																		numVertices(NumVertices), texture(Texture) {}
		GLuint offset;
		GLuint numVertices;
		GLuint texture;
	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		// initialize the sprite batch
		void init();

		//
		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, const GLuint texture, const float depth, const Color& color);
		void end();
			

		void renderBatch();

	private:
		void createRenderBatches();
		void createVertexArray();
		void sortGlyphs();
		
		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		GLuint _vbo;
		GLuint _vao;

		GlyphSortType _sortType;

		std::vector<Glyph*> _glyphs;
		std::vector<RenderBatch> _renderBatches;
	};

}

