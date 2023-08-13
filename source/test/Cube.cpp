#include <test/Cube.hpp>
#include<VertexBufferLayout.hpp>
#include<texture/Texture.hpp>
#include <vendor/glm/glm.hpp>


namespace Test {

	Cube::Cube(std::string testName) : Test(testName),
		ib(nullptr), vb(nullptr), va(nullptr), translate{ 0.0f, 0.0f, 0.0f },
		proj_matrix(glm::perspective(glm::radians(45.0f), (640.0f / 480.0f), 0.1f, 10.0f)), view_matrix(glm::mat4(1.0f)) {
		GLfloat vertPos[72] = {
			// FACE 1
			-0.5f,  0.5f,  0.5f,	//A - 0
			-0.5f,  0.5f, -0.5f,	//B - 1
			-0.5f, -0.5f, -0.5f,	//C - 2
			-0.5f, -0.5f,  0.5f,	//D - 3

			// FACE 2
			-0.5f,  0.5f, -0.5f,	//B - 4
			 0.5f,  0.5f, -0.5f,	//E - 5
			 0.5f, -0.5f, -0.5f,	//F - 6
			-0.5f, -0.5f, -0.5f,	//C - 7

			// FACE 3
			 0.5f,  0.5f, -0.5f,	//E - 8
			 0.5f,  0.5f,  0.5f,	//G - 9
			 0.5f, -0.5f,  0.5f,	//H - 10
			 0.5f, -0.5f, -0.5f,	//F - 11

			 // FACE 4

			-0.5f,  0.5f,  0.5f,	//A - 12
			-0.5f, -0.5f,  0.5f,	//D - 13
			 0.5f, -0.5f,  0.5f,	//H - 14
			 0.5f,  0.5f,  0.5f,	//G - 15

			 // FACE 5
			-0.5f,  0.5f,  0.5f,	//A - 16
			 0.5f,  0.5f,  0.5f,	//G - 17
			 0.5f,  0.5f, -0.5f,	//E - 18
			-0.5f,  0.5f, -0.5f,	//B - 19
			
			// FACE 6
			-0.5f, -0.5f, -0.5f,	//C - 20
			 0.5f, -0.5f, -0.5f,	//F - 21
			 0.5f, -0.5f,  0.5f,	//H - 22
			 -0.5f, -0.5f,  0.5f,	//D - 23
		};
		GLuint indices[36] = {
			0, 1, 2,		2, 3, 0,	// FACE 1 (ABCD)
			4, 5, 6,		6, 7, 4,	// FACE 2 (BEFC)
			8, 9, 10,		10, 11, 8,	// FACE 3 (EGHF)
			12, 13, 14,		14, 15, 12,	// FACE 4 (ADHG)
			16, 17, 18,		18, 19, 16,	// FACE 5 (AGEB)
			20, 21, 22,		22, 23, 20		// FACE 6 (CFHD)
		};

		va = new VertexArray();
		va->Bind();
		vb = new VertexBuffer(vertPos, 72 * sizeof(GLfloat));
		//		vb->Bind();
		//		vb->SetData(vertPos, 28 * sizeof(GLfloat));


		VertexArrayAttribute* vaa = new VertexArrayAttribute{
			0, 3, GL_FLOAT, GL_FALSE, "Position"
		};
		
		VertexBufferLayout* vbl = new VertexBufferLayout();
		vbl->Add(vaa);
		
		va->AddLayout(vbl, vb);

		//		ib = new IndexBuffer(indices, 15);
		ib = new IndexBuffer();
		ib->Bind();
		ib->SetData(indices, 36);

		std::string fileName = "res/Shaders/cube_shader.shader";
		shader = new Shader(fileName);
		shader->Bind();
		
	}

	Cube::~Cube() {
		delete va;
		delete vb;
		delete ib;
		//		delete texture;
		delete shader;
	}
	void Cube::OnUpdate(float deltaTime)
	{
	}
	void Cube::OnRender(Renderer& renderer)
	{
		view_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(translate[0] / 1.0f, translate[1] / 1.0f, translate[2] * 2));
		glm::mat4 mvp = proj_matrix * view_matrix;
		shader->SetUniformMat4f("u_MVP", mvp);

		renderer.Draw(va, ib, shader);
	}
	void Cube::OnImGuiRender()
	{
		ImGui::SliderFloat3("Position", translate, -5.0f, 5.0f);
	}
}