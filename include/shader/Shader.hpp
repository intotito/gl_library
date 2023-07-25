#pragma once
#include <GL/glew.h>
#include<string>
class Shader {
private:
	const GLuint m_type;
	const char* m_token;
protected:
	char* m_source;
	char* ParseShaderFile(const std::string& filePath);
	GLuint m_ID;
public:
	Shader(GLuint type, const char* token);
	virtual ~Shader();
	void CompileShader(const char* source);
	inline GLuint GetID() { return m_ID; }
};

