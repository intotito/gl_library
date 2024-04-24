#pragma once
#include<GL/glew.h>
#include<stdlib.h>
#include<string>
#include<iostream>
#include<sstream>
#include<assert.h>
#include <fstream>
#include<vendor/glm/glm.hpp>
#include<unordered_map>

class Shader {
private:
	GLuint m_ID;
	std::unordered_map<std::string, GLint> cachedUniformLocations;
	GLint GetUniformLocation(const char*);

public:
	Shader(std::string& filePath);
	~Shader();
	void CompileShader(GLuint shader, const char* source);
	void Bind();
	void Unbind();
	void SetUniform1i(const char* name, int value);
	void SetUniform1f(const char* name, float value);
	void SetUniform3fv(const char* name, GLfloat* values);
	void SetUniform4fv(const char* name, GLfloat* values);
	void SetUniformMat4f(const char* name, glm::mat4& matrix);
	void SetUniformMat3f(const char* name, glm::mat3& matrix);
	void SetUniform1iv(const char* name, GLint count, GLint* values);
	char* ParseShaderFile(const char* m_token, const std::string& filePath);
	inline GLuint GetID() { return m_ID; }
};

