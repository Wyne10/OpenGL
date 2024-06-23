#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>

namespace Shaders {
	class Shader
	{
	private:
		char* shaderSource;
		GLenum shaderType;
		GLuint shader;

		void loadShader(const char* path);
		void createShader();
		void compileShader();
		void deleteShader();
	public:
		Shader(const char* shader, GLenum shaderType, bool load = false);
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
		void deleteProgram();
	public:
		ShaderProgram(Shader* shaders[], size_t arraySize);
		~ShaderProgram();
		void printError();
		void useProgram();
		GLuint getShaderProgram();
	};
}