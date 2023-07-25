#include <shader/FragmentShader.hpp>
#include<assert.h>
#include<iostream>
FragmentShader::FragmentShader(std::string& filePath) : Shader(GL_FRAGMENT_SHADER, "#SHADER FRAGMENT")
{
	m_source = ParseShaderFile(filePath);
	CompileShader(m_source);
}
FragmentShader::~FragmentShader()
{
	free(m_source);
}
