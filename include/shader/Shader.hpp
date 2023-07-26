#pragma once
#include<Renderer.hpp>

class Shader {
private:
	GLuint m_ID;
public:
	Shader(std::string& filePath);
	~Shader();
	void CompileShader(GLuint shader, const char* source);
	void Bind();
	void Unbind();
	void SetUniform3fv(const char* name, GLfloat* values);
	void SetUniform4fv(const char* name, GLfloat* values);
	char* ParseShaderFile(const char* m_token, const std::string& filePath);
	inline GLuint GetID() { return m_ID; }

};

