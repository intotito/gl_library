#include <shader/Shader.hpp>
#include<iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
Shader::Shader(GLuint type, const char* token) : m_type(type), m_token(token), m_source(0), m_ID(NULL)
{

}

Shader::~Shader()
{
}

void Shader::CompileShader(const char* source)
{
    GLint compile;
    std::cout << "Shader Source" << std::endl << source << std::endl;
    m_ID = glCreateShader(m_type);
    if (m_ID == GL_FALSE) {
        assert(false);
    }
    glShaderSource(m_ID, 1, &source, nullptr);
    glCompileShader(m_ID);
    glGetShaderiv(m_ID, GL_COMPILE_STATUS, &compile);
    if (compile == GL_FALSE) {
        GLint infoLength;
        glGetShaderiv(m_ID, GL_INFO_LOG_LENGTH, &infoLength);
        GLchar* msg = (char*)malloc(infoLength * sizeof(char));
        glGetShaderInfoLog(m_ID, infoLength, NULL, msg);
        std::cout << "Error " << msg << std::endl;
        free(msg);
        glDeleteProgram(m_ID);
        assert(false);
    }
}

char* Shader::ParseShaderFile(const std::string& filePath)
{
    std::cout << filePath << std::endl;
    std::ifstream sFile(filePath);
    std::string line;
    std::stringstream ss;
    bool start = false;
    while (getline(sFile, line)) {
        if (!start && line.compare(m_token) == 0)
        {
            start = true;
        }
        else if (start && line.compare(0, 7, "#SHADER") == 0) {
            start = false;
            break;
        }
        else if (start)
        {
            ss << line << std::endl;
        }
    }
    int length = strlen(ss.str().c_str());
    char* source = (char*)malloc(sizeof(char) * length + 1);
    strcpy(source, ss.str().c_str());
    return source;
}
