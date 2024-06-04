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
#include<Camera.hpp>
#include<Jaw.hpp>

namespace Test {
	class Cube : public Test {
	public:
		Cube(std::string name);
		~Cube();
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
		float m_angle = 0.0f;
		float lightPosition[3];
		glm::vec3 m_LookAt;
		Camera* camera;
		Jaw jaw;
	};
}