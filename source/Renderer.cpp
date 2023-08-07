
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

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::Clear()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(VertexArray* va, IndexBuffer* ib, Shader* shader)
{
    va->Bind();
    ib->Bind();
    shader->Bind();
    GLtry(
  //      glDrawArrays(GL_TRIANGLES, 5, 3);
        glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr)
    );
}
