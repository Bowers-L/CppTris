#include "IndexBuffer.h"

#include "Engine/Log.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count, GLenum usage)
	: m_Count(count)
{
	GL_CALL(glGenBuffers(1, &m_BufferID));
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
	GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, usage));
}

IndexBuffer::~IndexBuffer()
{
	GL_CALL(glDeleteBuffers(1, &m_BufferID));
}

void IndexBuffer::bind() const
{
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
}

void IndexBuffer::unbind() const
{
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
