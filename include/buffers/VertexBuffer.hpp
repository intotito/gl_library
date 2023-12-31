#pragma once
#include<GL/glew.h>
class Object;
class VertexBuffer
{
private:
	GLuint m_ID;
public:
	VertexBuffer();
	VertexBuffer(Object& object);
	VertexBuffer(const void* data, const GLuint size);
	~VertexBuffer();
	void Bind() const;
	void Unbind() const;
	void SetData(const void* data, const GLuint size);
	inline GLuint GetID() { return m_ID; }
};