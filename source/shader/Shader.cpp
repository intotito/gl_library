#include <shader/Shader.hpp>


Shader::Shader(std::string& filePath)
{
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
 //   if (vShader == GL_FALSE) {
 //       assert(false);
 //   }
    char* source = ParseShaderFile("#SHADER VERTEX", filePath);
    CompileShader(vShader, source);
    free(source);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    //    if (fShader == GL_FALSE) {
    //        assert(false);
    //    }
    source = ParseShaderFile("#SHADER FRAGMENT", filePath);
    CompileShader(fShader, source);
    free(source);
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vShader);
    glAttachShader(m_ID, fShader);
    GLint linked;
    glLinkProgram(m_ID);

    glGetProgramiv(m_ID, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE) {
        int infoLength;
        glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &infoLength);
        GLchar* msg = (GLchar*)malloc(sizeof(GLchar) * infoLength);
        glGetProgramInfoLog(m_ID, infoLength, NULL, msg);
        std::cout << "Error " << msg << std::endl;
        free(msg);
        glDeleteProgram(m_ID);
    }
}


Shader::~Shader()
{
}

void Shader::Bind() 
{
    glUseProgram(m_ID);
}

void Shader::Unbind() {
    glUseProgram(0);
}

void Shader::CompileShader(GLuint shader, const char* source)
{
    GLint compile;
    std::cout << "Shader Source" << std::endl << source << std::endl;
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile);
    if (compile == GL_FALSE) {
        GLint infoLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
        GLchar* msg = (char*)malloc(infoLength * sizeof(char));
        glGetShaderInfoLog(shader, infoLength, NULL, msg);
        std::cout << "Error " << msg << std::endl;
        free(msg);
        glDeleteShader(shader);
        assert(false);
    }
}

char* Shader::ParseShaderFile(const char* m_token, const std::string& filePath)
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
