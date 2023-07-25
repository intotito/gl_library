#include <shader/VertexShader.hpp>
#include<assert.h>
#include<iostream>
VertexShader::VertexShader(std::string& filePath) : Shader(GL_VERTEX_SHADER, "#SHADER VERTEX")
{
    m_source = ParseShaderFile(filePath);
	CompileShader(m_source);
}
VertexShader::~VertexShader()
{
	free(m_source);
}
