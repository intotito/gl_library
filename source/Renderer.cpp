
#include <Renderer.hpp>
void ClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool CheckError(const char* file, const char* function, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error]: (" << error << ") at Line: " << line << " function: " << function << " File: " << file << std::endl;
        return false;
    }
    return true;
}

Renderer::Renderer()// : current_scene(nullptr)
{

}

Renderer::~Renderer()
{

}

/*
void Renderer::AddScene(Scene* scene) {
    scenes.push_back(scene);
    if (current_scene == nullptr)
    {
        current_scene = scene;
    }
}
*/
void Renderer::Clear()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(VertexArray* va, IndexBuffer* ib, Shader* shader)
{
    va->Bind();
    ib->Bind();
    shader->Bind();
    Clear();
    GLtry(
  //      glDrawArrays(GL_TRIANGLES, 5, 3);
        glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr)
    );
}
