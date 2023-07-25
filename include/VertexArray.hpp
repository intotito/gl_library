#pragma once
#include<buffers/VertexBuffer.hpp>
#include<string>
#include <GL/glew.h>
#include<assert.h>
#include<VertexBufferLayout.hpp>

class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void Bind();
	void Unbind();
//	void LinkAttribute(VertexArrayAttribute* vaa, VertexBuffer* vb);
	void AddLayout(VertexBufferLayout vbl, VertexBuffer* vb);

private:
	//	std::vector<VertexArrayAttribute*> attributes;
	GLuint m_ID;
	GLuint stride = 0;
};