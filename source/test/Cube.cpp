#include <test/Cube.hpp>
#include<VertexBufferLayout.hpp>
#include<texture/Texture.hpp>
#include <vendor/glm/glm.hpp>


namespace Test {

	Cube::Cube(std::string testName) : Test(testName), m_LookAt(glm::vec3(0.0f, 0.0f, 0.0f)),
		camera(new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))),
		ib(nullptr), vb(nullptr), va(nullptr), translate{ 0.0f, 0.0f, 0.0f }, lightPosition{0.0f, 00.0f, 5.0f },
		proj_matrix(glm::perspective(glm::radians(45.0f), (640.0f / 480.0f), 1.f, 100.0f)), view_matrix(glm::mat4(1.0f)) {
		GLfloat vertPos[144] = {
			// FACE 1 - Position	-	Normal
			 0.5f,  0.5f,  0.5f,	 0.0f, 0.0f, 1.0f,	//A - 0
			-0.5f,  0.5f,  0.5f,	 0.0f, 0.0f, 1.0f,	//B - 1
			-0.5f, -0.5f,  0.5f,	 0.0f, 0.0f, 1.0f,	//C - 2
			 0.5f, -0.5f,  0.5f,	 0.0f, 0.0f, 1.0f,	//D - 3

			// FACE 2 - Position	-	Normal
			-0.5f,  0.5f,  0.5f,	-1.0f, 0.0f, 0.0f,	//B - 4
			-0.5f,  0.5f, -0.5f,	-1.0f, 0.0f, 0.0f,	//E - 5
			-0.5f, -0.5f, -0.5f,	-1.0f, 0.0f, 0.0f,	//F - 6
			-0.5f, -0.5f,  0.5f,	-1.0f, 0.0f, 0.0f,	//C - 7

			// FACE 3 - Position	-	Normal
			-0.5f,  0.5f, -0.5f,	 0.0f, 0.0f, -1.0f,	//E - 8
			 0.5f,  0.5f, -0.5f,	 0.0f, 0.0f, -1.0f,	//G - 9
			 0.5f, -0.5f, -0.5f,	 0.0f, 0.0f, -1.0f,	//H - 10
			-0.5f, -0.5f, -0.5f,	 0.0f, 0.0f, -1.0f,	//F - 11

			 // FACE 4 - Position	-	Normal

			 0.5f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	//A - 12
			 0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	//D - 13
			 0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	//H - 14
			 0.5f,  0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	//G - 15

			 // FACE 5 - Position	-	Normal
			 0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	//A - 16
			 0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	//G - 17
			-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	//E - 18
			-0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	//B - 19
			
			// FACE 6 - Position	-	Normal
			-0.5f, -0.5f,  0.5f,	0.0f, -1.0f, 0.0f,	//C - 20
			-0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,	//F - 21
			 0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,	//H - 22	
			 0.5f, -0.5f,  0.5f,	0.0f, -1.0f, 0.0f	//D - 23
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
		vb = new VertexBuffer(vertPos, 144 * sizeof(GLfloat));
		//		vb->Bind();
		//		vb->SetData(vertPos, 28 * sizeof(GLfloat));


		VertexArrayAttribute* vaa = new VertexArrayAttribute{
			0, 3, GL_FLOAT, GL_FALSE, "Position"
		};

		VertexArrayAttribute* vaa1 = new VertexArrayAttribute{
			1, 3, GL_FLOAT, GL_FALSE, "Normal"
		};
		
		VertexBufferLayout* vbl = new VertexBufferLayout();
		vbl->Add(vaa);
		vbl->Add(vaa1);
		
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
		delete camera;
	}
	void Cube::OnUpdate(float deltaTime)
	{
	}
	void Cube::OnRender(Renderer& renderer)
	{
		float angle = (float)glfwGetTime() / 10.0f;
		glm::mat4 rotate(
			glm::cos(angle), glm::sin(angle), 0.0f, 0.0f,
			-sin(angle), glm::cos(angle), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		float ambient[3] = {1.0f, 0.5f, 0.31f};
		float diffuse[3] = {1.0f, 0.5f, 0.31f};
		float specular[3] = { 0.5f, 0.5f, 0.5f};
		float shininess = 32.0f;
		float lightColor[3] = { 1.0f, 1.0f, 1.0f };


		//	const float radius = 5.0f;
		camera->SetX(glm::sin(glm::radians(m_angle)) * 10.0f);
		camera->SetZ(glm::cos(glm::radians(m_angle)) * 10.0f);
		camera->SetLookAt(m_LookAt);

		glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f),
			glm::vec3(translate[0], translate[1], translate[2])) * glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
		view_matrix = camera->GetMatrix();// glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.0f, -10.0f));
		glm::mat4 mvp = proj_matrix * view_matrix * model_matrix;
		glm::mat4 model = model_matrix;
		glm::mat3 transInv = glm::mat3(glm::transpose(glm::inverse(model)));
		shader->SetUniformMat4f("u_MVP", mvp);
		shader->SetUniformMat4f("u_MODEL", model);
		shader->SetUniformMat3f("u_TransInv", transInv);
//		shader->SetUniform3fv("u_LightPos", lightPosition);

		shader->SetUniform3fv("light.position", lightPosition);
		shader->SetUniform3fv("light.color", lightColor);
		shader->SetUniform1f("light.ambient", 0.2f);
		shader->SetUniform1f("light.diffuse", 0.5f);
		shader->SetUniform1f("light.specular", 1.0f);

		shader->SetUniform3fv("material.ambient", ambient);
		shader->SetUniform3fv("material.diffuse", diffuse);
		shader->SetUniform3fv("material.specular", specular);
		shader->SetUniform1f("material.shininess", shininess);


	//	float cameraPos[3] = { camera->GetX(), camera->GetY(), camera->GetZ() };
		shader->SetUniform3fv("u_CameraPos", &(camera->GetPosition()[0]));
		

		renderer.Draw(va, ib, shader);
	}
	void Cube::OnImGuiRender()
	{
		ImGui::SliderFloat3("Position", translate, -5.0f, 5.0f);
		ImGui::SliderFloat("Camera Position", &m_angle, -180, 180);
		ImGui::SliderFloat3("Camera Look At", &(m_LookAt.x), -10, 10);
	}
}