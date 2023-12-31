#pragma once
#include <GL/glew.h>
#include<string>
#include <vector>
#include <assert.h>


struct VertexArrayAttribute {
	GLuint index;
	GLuint count;
	GLuint type = GL_FLOAT;
	GLuint normalized = GL_FALSE;
	std::string name;
	int GetSize() const {
		switch (type)
		{
		case GL_FLOAT:
			return sizeof(GLfloat);
		default:
			assert(false);
		}
	}
};

class VertexBufferLayout {
public:
	VertexBufferLayout();
	~VertexBufferLayout();
	void Add(VertexArrayAttribute* vaa);
	const std::vector<VertexArrayAttribute*> GetAttributes() const;
	inline int GetStride() { return stride; }
private:
	std::vector<VertexArrayAttribute*> attributes;
	int stride;
};