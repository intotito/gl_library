#pragma once
#include<string>
#include<GL/glew.h>
#include<iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
class Shader {
private:
	GLuint m_ID;
protected:
	char* ParseShaderFile(const char* m_token, const std::string& filePath);
public:
	Shader(std::string& filePath);
	~Shader();
	void CompileShader(GLuint shader, const char* source);
	inline GLuint GetID() { return m_ID; }
	void Bind();
	void Unbind();
};

