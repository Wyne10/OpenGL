#pragma once
#include <glad/glad.h>
#include "shader.h"
#include <iostream>

namespace Drawing {
	class Object {
	protected:
		void* data;
		GLuint VBO, VAO;

		Object();

		virtual void generateBuffers();
		virtual void bindBuffers();
		virtual void bufferData(GLsizeiptr size, GLenum usage);
		virtual void deleteBuffers();
	public:
		Object(void* data, GLsizeiptr size, GLenum usage);
		~Object();
		void vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
		void enableVertexAttribArray(GLuint index);
		void unbindBuffers();
		void draw(GLenum mode, GLint first, GLsizei count);
	};

	class ElementObject : public Object
	{
	private:
		void* indices;
		GLuint EBO;

		void generateBuffers() override;
		void bindBuffers() override;
		void bufferData(GLsizeiptr size, GLsizeiptr indicesSize, GLenum usage);
		void deleteBuffers() override;

	public:
		ElementObject(void* data, void* indices, GLsizeiptr size, GLsizeiptr indicesSize, GLenum usage);
		~ElementObject();
		void draw(GLenum mode, GLsizei count, GLenum type, const void* indices);
	};
}