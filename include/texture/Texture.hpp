#pragma once
#include <GL/glew.h>
#include <string>
class Texture {
private:
//	GLuint m_ID;
	static  GLuint slot;

//	std::string filePath;
//	GLubyte* localBuffer;
//	int width, height, bpp;
public:
	Texture();
	~Texture();
	static GLuint LoadTexture(const char* filePath);
	static void Bind(GLuint unit, GLuint slot) ;
	static void Unbind() ;
};
