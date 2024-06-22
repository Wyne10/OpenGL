#pragma once
#include <glad/glad.h>

namespace Shaders {
	class Shader
	{
	private:
		const char* shaderSource;
		GLenum shaderType;
		GLuint shader;

		void createShader();
		void compileShader();
		void deleteShader();
	public:
		Shader(const char* shaderSource, GLenum shaderType);
		~Shader();
		void printError();
		GLuint getShader();
	};

	class ShaderProgram
	{
	private:
		GLuint shaderProgram;

		void createProgram();
		void attachShader(Shader* shader);
		void linkProgram();
	public:
		ShaderProgram(Shader* shaders[], size_t arraySize);
		void printError();
		void useProgram();
		GLuint getShaderProgram();
	};
}