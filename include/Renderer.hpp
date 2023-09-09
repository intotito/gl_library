#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <VertexArray.hpp>
#include<buffers/IndexBuffer.hpp>
#include<shader/Shader.hpp>
//#include<Scene.hpp>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLtry(x) ClearError(); x; ASSERT(CheckError(__FILE__, #x, __LINE__));0

void ClearError();
bool CheckError(const char* file, const char* function, int line);
class Renderer {
public:
    Renderer();
    ~Renderer();
 //   void AddScene(Scene* scene);
    void Clear();
    void Draw(VertexArray* va, IndexBuffer* ib, Shader* shader); 
private:
 //   std::vector<Scene*> scenes;
 //   Scene* current_scene;
};