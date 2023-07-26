#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <VertexArray.hpp>
#include<buffers/IndexBuffer.hpp>
#include<shader/Shader.hpp>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLtry(x) ClearError(); x; ASSERT(CheckError(__FILE__, #x, __LINE__));

void ClearError();
bool CheckError(const char* file, const char* function, int line);
class Renderer {
public:
    Renderer();
    ~Renderer();
    void Draw(VertexArray* va, IndexBuffer* ib, Shader* shader);    
};