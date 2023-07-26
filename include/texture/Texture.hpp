#pragma once
#include <GL/glew.h>
#include <string>
class Texture {
private:
	GLuint m_ID;
	std::string filePath;
	GLubyte* localBuffer;
	int width, height, bpp;
public:
	Texture(const char* filePath);
	~Texture();
	inline int GetWidth() const{ return width; }
	inline int GetHeight() const{ return height; }
	inline int GetBPP() const{ return bpp; }
	void Bind(GLuint slot = 0) const;
	void Unbind() const;
};