#include "drawing.h"

#pragma region Object
Drawing::Object::Object()
{}

Drawing::Object::Object(void* data, GLsizeiptr size, GLenum usage)
{
	this->data = data;
	generateBuffers();
	bindBuffers();
	bufferData(size, usage);
}

Drawing::Object::~Object()
{
	deleteBuffers();
}

void Drawing::Object::generateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
}

void Drawing::Object::bindBuffers()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void Drawing::Object::unbindBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Drawing::Object::bufferData(GLsizeiptr size, GLenum usage)
{
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void Drawing::Object::deleteBuffers()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Drawing::Object::vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void Drawing::Object::enableVertexAttribArray(GLuint index)
{
	glEnableVertexAttribArray(index);
}

void Drawing::Object::draw(GLenum mode, GLint first, GLsizei count)
{
	glBindVertexArray(VAO);
	glDrawArrays(mode, first, count);
}
#pragma endregion

#pragma region ElementObject
Drawing::ElementObject::ElementObject(void* data, void* indices, GLsizeiptr size, GLsizeiptr indicesSize, GLenum usage)
{
	this->data = data;
	this->indices = indices;
	generateBuffers();
	bindBuffers();
	bufferData(size, indicesSize, usage);
}

Drawing::ElementObject::~ElementObject()
{
	deleteBuffers();
}

void Drawing::ElementObject::generateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

void Drawing::ElementObject::bindBuffers()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void Drawing::ElementObject::bufferData(GLsizeiptr size, GLsizeiptr indicesSize, GLenum usage)
{
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, usage);
}

void Drawing::ElementObject::deleteBuffers()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Drawing::ElementObject::draw(GLenum mode, GLsizei count, GLenum type, const void* indices)
{
	glBindVertexArray(VAO);
	glDrawElements(mode, count, type, indices);
}
#pragma endregion
