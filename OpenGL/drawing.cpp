#include "drawing.h"

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