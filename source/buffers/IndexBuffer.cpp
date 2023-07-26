#include<buffers/IndexBuffer.hpp>

IndexBuffer::IndexBuffer(): count(0)
{
	glGenBuffers(1, &m_ID);
}

IndexBuffer::IndexBuffer(const void* data, const GLuint count): IndexBuffer()
{
//	glGenBuffers(1, &m_ID);
	IndexBuffer::count = count;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * count, data, GL_STATIC_DRAW);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::SetData(const void* data, const GLuint count)
{
	Bind();
	IndexBuffer::count = count;
	glBufferData(m_ID, sizeof(GLuint) * count, data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_ID);
}
