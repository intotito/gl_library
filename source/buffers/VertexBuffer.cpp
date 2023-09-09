#include<buffers/VertexBuffer.hpp>
#include<Object.hpp>

VertexBuffer::VertexBuffer(): m_ID(0)
{
	glGenBuffers(1, &m_ID);
}

VertexBuffer::VertexBuffer(Object& object): m_ID(0)
{
	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	glBufferData(GL_ARRAY_BUFFER, object.GetByteSize(), nullptr, GL_DYNAMIC_DRAW);
	auto& v = object.GetMeshes();
	GLfloat offset = 0;
	for(int i = 0; i < v.size(); i++){
		glBufferSubData(GL_ARRAY_BUFFER, offset, v[i].GetByteSize(), v[i].Data());
		offset += v[i].GetByteSize();
	}
	object.SetBuffer(m_ID);
}

VertexBuffer::VertexBuffer(const void* data, const GLuint size): m_ID(0)
{
	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData(const void* data, const GLuint size)
{
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	Unbind();
	glDeleteBuffers(1, &m_ID);
}
