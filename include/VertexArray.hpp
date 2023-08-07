#pragma once
//#include <Renderer.hpp>
#include<buffers/VertexBuffer.hpp>
#include<VertexBufferLayout.hpp>

class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void Bind();
	void Unbind();
//	void LinkAttribute(VertexArrayAttribute* vaa, VertexBuffer* vb);
	void AddLayout(VertexBufferLayout* vbl, VertexBuffer* vb);

private:
	//	std::vector<VertexArrayAttribute*> attributes;
	GLuint m_ID;
	GLuint stride = 0;
};