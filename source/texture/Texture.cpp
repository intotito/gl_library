#include<texture/Texture.hpp>
#include<vendor/stb_image/stb_image.h>

GLuint Texture::slot = 0;
Texture::Texture()
{

}
Texture::~Texture()
{
	Unbind();
}
GLuint Texture::LoadTexture(const char* path)
{
	GLuint unit;
	int width, height, bpp;
	stbi_set_flip_vertically_on_load(1);
	GLubyte* localBuffer = stbi_load(path, &width, &height, &bpp, 4);
	glGenTextures(1, &unit);
	glBindTexture(GL_TEXTURE_2D, unit);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
	glBindTexture(GL_TEXTURE_2D, unit);
	if (localBuffer)
		stbi_image_free(localBuffer);
	Texture::slot++;
	return unit;
}

void Texture::Bind(GLuint unit, GLuint slot) 
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, unit);
}

void Texture::Unbind() 
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

