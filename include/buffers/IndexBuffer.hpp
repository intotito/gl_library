#pragma once
#include <GL/glew.h>
class IndexBuffer
{
private:
	GLuint m_ID;
	GLuint count;
public:
	IndexBuffer();
	IndexBuffer(const void* data, const GLuint count);
	~IndexBuffer();
	void Bind() const;
	void Unbind() const;
	void SetData(const void* data, const GLuint count);
	inline GLuint GetCount() { return count; }
	inline void SetCount(GLuint count) { IndexBuffer::count = count; }
};