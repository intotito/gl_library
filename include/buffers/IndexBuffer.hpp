#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class IndexBuffer
{
private:
	GLuint m_ID;
public:
	IndexBuffer();
	IndexBuffer(const void* data, const GLuint count);
	~IndexBuffer();
	void Bind() const;
	void Unbind() const;
	void SetData(const void* data, const GLuint count);
};