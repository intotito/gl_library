#include <test/Texture2D.hpp>
#include<VertexBufferLayout.hpp>
#include<texture/Texture.hpp>
#include <vendor/glm/glm.hpp>


namespace Test {

	Texture2D::Texture2D(std::string testName) : Test(testName), 
		ib(nullptr), vb(nullptr), va(nullptr), translate{ 0.0f, 0.0f, 0.0f },
		proj_matrix(glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f)), view_matrix(glm::mat4(1.0f)) {
		GLfloat vertPos[] = {
			-0.25f, 0.5f,  0.25f, 1.0f, //A
			-0.5f,	0.0f,	0.0f, 0.5f,	//B
			0.0f,	0.0f,	0.5f, 0.5f,	//C
			-0.5f,	-0.5f,	0.0f, 0.0f,	//D
			0.0f,	-0.5f,	0.5f, 0.0f,	//E
			0.5f,	0.0f,	1.0f, 0.5f, //F
			0.5f,	-0.5f,	1.0f, 0.0f	//G
		};
		GLuint indices[] = {
			0, 1, 2,
			1, 2, 3,
			2, 3, 4,
			2, 4, 5,
			4, 5, 6
		};

		va = new VertexArray();
		va->Bind();
		vb = new VertexBuffer(vertPos, 28 * sizeof(GLfloat));
//		vb->Bind();
//		vb->SetData(vertPos, 28 * sizeof(GLfloat));

		
		VertexArrayAttribute* vaa = new VertexArrayAttribute{
			0, 2, GL_FLOAT, GL_FALSE, "Position"
		};	
		VertexArrayAttribute* vaa2 = new VertexArrayAttribute{
			1, 2, GL_FLOAT, GL_FALSE, "Texture_Coord"
		};
		VertexBufferLayout* vbl = new VertexBufferLayout();
		vbl->Add(vaa);
		vbl->Add(vaa2);
		va->AddLayout(vbl, vb);
		
//		ib = new IndexBuffer(indices, 15);
		ib = new IndexBuffer();
		ib->Bind();
		ib->SetData(indices, 15);
		
		std::string fileName = "res/Shaders/Basic.shader";
		shader = new Shader(fileName);
		shader->Bind();
		GLuint texture1 = Texture::LoadTexture("res/textures/Camo.png");
		Texture::Bind(texture1, 0);
//		texture = new Texture("res/textures/Camo.png");
//		texture->Bind(0);
		shader->SetUniform1i("u_Texture", 0);
	}

	Texture2D::~Texture2D() {
		delete va;
		delete vb;
		delete ib;
//		delete texture;
		delete shader;
	}
	void Texture2D::OnUpdate(float deltaTime)
	{
	}
	void Texture2D::OnRender(Renderer& renderer)
	{
		view_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(translate[0], translate[1], translate[2]));
		glm::mat4 mvp = proj_matrix * view_matrix;
		shader->SetUniformMat4f("u_MVP", mvp);

		renderer.Draw(va, ib, shader);
	}
	void Texture2D::OnImGuiRender()
	{
		ImGui::SliderFloat3("Position", translate, -0.5f, 0.5f);
	}
}