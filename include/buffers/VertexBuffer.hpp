#pragma once
#include<GL/glew.h>
class VertexBuffer
{
private:
	GLuint m_ID;
public:
	VertexBuffer();
	VertexBuffer(const void* data, const GLuint size);
	~VertexBuffer();
	void Bind() const;
	void Unbind() const;
	void SetData(const void* data, const GLuint size);
};