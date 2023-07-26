
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

void Renderer::Draw(VertexArray* va, IndexBuffer* ib, Shader* shader)
{
    va->Bind();
    ib->Bind();
    shader->Bind();
    GLtry(
        glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr)
    );
}
