#include "VertexBuffer.h"

#include "Engine/Log.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size, GLenum usage)
{
	GL_CALL(glGenBuffers(1, &m_BufferID));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
}

VertexBuffer::~VertexBuffer()
{
	GL_CALL(glDeleteBuffers(1, &m_BufferID));
}

void VertexBuffer::updateBuffer(GLintptr offset, GLsizeiptr size, GLvoid * data) {
	GL_CALL(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
}

void VertexBuffer::bind() const
{
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
}

void VertexBuffer::unbind() const
{
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
