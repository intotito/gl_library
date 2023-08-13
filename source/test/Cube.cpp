#include <test/Cube.hpp>
#include<VertexBufferLayout.hpp>
#include<texture/Texture.hpp>
#include <vendor/glm/glm.hpp>


namespace Test {

	Cube::Cube(std::string testName) : Test(testName),
		ib(nullptr), vb(nullptr), va(nullptr), translate{ 0.0f, 0.0f, 0.0f },
		proj_matrix(glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f)), view_matrix(glm::mat4(1.0f)) {
		GLfloat vertPos[24] = {
			-0.5f,  0.5f,  0.5f,	//A - 0
			-0.5f,  0.5f, -0.5f,	//B - 1
			-0.5f, -0.5f, -0.5f,	//C - 2
			-0.5f, -0.5f,  0.5f,	//D - 3
			 0.5f,  0.5f, -0.5f,	//E - 4
			 0.5f, -0.5f, -0.5f,	//F - 5
			 0.5f,  0.5f,  0.5f,	//G - 6
			 0.5f, -0.5f,  0.5f,	//H - 7
		};
		GLuint indices[36] = {
			0, 1, 2,	0, 2, 3,	// FACE 1 (ABCD)
			1, 4, 5,	1, 5, 3,	// FACE 2 (BEFC)
			4, 6, 7,	6, 7, 5,	// FACE 3 (EGHF)
			0, 4, 1,	0, 6, 4,	// FACE 4 (ADHG)
			0, 6, 4,	6, 4, 1,	// FACE 5 (AGEB)
			2, 5, 7,	5, 7, 3
		};

		va = new VertexArray();
		va->Bind();
		vb = new VertexBuffer(vertPos, 24 * sizeof(GLfloat));
		//		vb->Bind();
		//		vb->SetData(vertPos, 28 * sizeof(GLfloat));


		VertexArrayAttribute* vaa = new VertexArrayAttribute{
			0, 2, GL_FLOAT, GL_FALSE, "Position"
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
		view_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(translate[0], translate[1], translate[2]));
		glm::mat4 mvp = proj_matrix * view_matrix;
		shader->SetUniformMat4f("u_MVP", mvp);

		renderer.Draw(va, ib, shader);
	}
	void Cube::OnImGuiRender()
	{
		ImGui::SliderFloat3("Position", translate, -0.5f, 0.5f);
	}
}