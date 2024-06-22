#include "shader.h"
#include <iostream>

#pragma region Shader
Shaders::Shader::Shader(const char* shaderSource, GLenum shaderType)
{
	this->shaderSource = shaderSource;
	this->shaderType = shaderType;
	createShader();
	compileShader();
}

Shaders::Shader::~Shader()
{
	deleteShader();
}

void Shaders::Shader::createShader()
{
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
}

void Shaders::Shader::compileShader()
{
	glCompileShader(shader);
}

void Shaders::Shader::deleteShader()
{
	glDeleteShader(shader);
}

void Shaders::Shader::printError()
{
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

GLuint Shaders::Shader::getShader()
{
	return shader;
}
#pragma endregion

#pragma region ShaderProgram
Shaders::ShaderProgram::ShaderProgram(Shader* shaders[], size_t arraySize)
{
	createProgram();
	for (int i = 0; i < arraySize; i++)
	{
		attachShader(shaders[i]);
	}
	linkProgram();
}

void Shaders::ShaderProgram::createProgram()
{
	shaderProgram = glCreateProgram();
}

void Shaders::ShaderProgram::attachShader(Shader* shader)
{
	glAttachShader(shaderProgram, shader->getShader());
}

void Shaders::ShaderProgram::linkProgram()
{
	glLinkProgram(shaderProgram);
}

void Shaders::ShaderProgram::printError()
{
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADERPROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}
}

void Shaders::ShaderProgram::useProgram()
{
	glUseProgram(shaderProgram);
}

GLuint Shaders::ShaderProgram::getShaderProgram()
{
	return shaderProgram;
}
#pragma endregion
