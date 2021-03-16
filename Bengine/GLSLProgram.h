#pragma once

#include <string>
#include <GL/glew.h>
#include "Error.h"
#include <fstream>
#include <vector>

namespace Bengine {
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		void linkShaders();
		void addAttribute(const std::string& attributeName);
		void use();
		void unuse();
		GLint getUniformLocation(const std::string& uniformName);

	private:
		void compileShader(const std::string& filePath, GLuint id);

		GLint _numAttributes;

		GLuint _programID;
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;
	};

}