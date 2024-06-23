#pragma once
#include <glad/glad.h>
#include "shader.h"
#include <iostream>

namespace Drawing {
	class Object {
	private:
		void* data;
		GLuint VBO, VAO;

		void generateBuffers();
		void bindBuffers();
		void bufferData(GLsizeiptr size, GLenum usage);
		void deleteBuffers();
	public:
		Object(void* data, GLsizeiptr size, GLenum usage);
		~Object();
		void vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
		void enableVertexAttribArray(GLuint index);
		void unbindBuffers();
		void draw(GLenum mode, GLint first, GLsizei count);
	};
}