#pragma once
#include<test/Test.hpp>
#include<string>
#include <VertexArray.hpp>
#include<VertexBufferLayout.hpp>
#include<buffers/IndexBuffer.hpp>
#include<buffers/VertexBuffer.hpp>
#include<VertexArray.hpp>
#include<shader/Shader.hpp>
#include<texture/Texture.hpp>
#include<vendor/glm/gtc/matrix_transform.hpp>

namespace Test {
	class Texture2D : public Test {
	public:
		Texture2D(std::string name);
		~Texture2D();
		void OnUpdate(float deltaTime) override;
		void OnRender(Renderer& renderer, float deltaTime) override;
		void OnImGuiRender() override;
	private:
		VertexArray* va;
		VertexBuffer* vb;
		IndexBuffer* ib;
		Shader* shader;
		glm::mat4 proj_matrix;
		glm::mat4 view_matrix;
		float translate[3];
		Texture* texture;
	};
}