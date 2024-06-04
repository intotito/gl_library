#include <test/Cube.hpp>
#include<VertexBufferLayout.hpp>
#include<texture/Texture.hpp>
#include <vendor/glm/glm.hpp>


namespace Test {

	Cube::Cube(std::string testName) : Test(testName), m_LookAt(glm::vec3(0.0f, 0.0f, -1.0f)),
		camera(new Camera(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f))), jaw(Jaw()),
		ib(nullptr), vb(nullptr), va(nullptr), translate{ 0.0f, 0.0f, 0.0f }, lightPosition{0.0f, 00.0f, 5.0f },
		proj_matrix(glm::perspective(glm::radians(45.0f), (640.0f / 480.0f), 1.f, 100.0f)), view_matrix(glm::mat4(1.0f)) {
		GLfloat vertPos[192] = {
			// FACE 1 - Position	-	Normal			-	Texture Coordinate
			 0.5f,  0.5f,  0.5f,	 0.0f, 0.0f, 1.0f,		1.0f, 1.0f,	//A - 0
			-0.5f,  0.5f,  0.5f,	 0.0f, 0.0f, 1.0f,		0.0f, 1.0f,	//B - 1
			-0.5f, -0.5f,  0.5f,	 0.0f, 0.0f, 1.0f,		0.0f, 0.0f,	//C - 2
			 0.5f, -0.5f,  0.5f,	 0.0f, 0.0f, 1.0f,		1.0f, 0.0f,	//D - 3

			// FACE 2 - Position	-	Normal
			-0.5f,  0.5f,  0.5f,	-1.0f, 0.0f, 0.0f,		1.0f, 1.0f,	//B - 4
			-0.5f,  0.5f, -0.5f,	-1.0f, 0.0f, 0.0f,		0.0f, 1.0f,	//E - 5
			-0.5f, -0.5f, -0.5f,	-1.0f, 0.0f, 0.0f,		0.0f, 0.0f,	//F - 6
			-0.5f, -0.5f,  0.5f,	-1.0f, 0.0f, 0.0f,		1.0f, 0.0f,	//C - 7

			// FACE 3 - Position	-	Normal
			-0.5f,  0.5f, -0.5f,	 0.0f, 0.0f, -1.0f,		1.0f, 1.0f,	//E - 8
			 0.5f,  0.5f, -0.5f,	 0.0f, 0.0f, -1.0f,		0.0f, 1.0f,	//G - 9
			 0.5f, -0.5f, -0.5f,	 0.0f, 0.0f, -1.0f,		0.0f, 0.0f,	//H - 10
			-0.5f, -0.5f, -0.5f,	 0.0f, 0.0f, -1.0f,		1.0f, 0.0f,	//F - 11

			 // FACE 4 - Position	-	Normal

			 0.5f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f,		0.0f, 1.0f,	//A - 12
			 0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 0.0f,		0.0f, 0.0f,	//D - 13
			 0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,		1.0f, 0.0f,	//H - 14
			 0.5f,  0.5f, -0.5f,	1.0f, 0.0f, 0.0f,		1.0f, 1.0f,	//G - 15

			 // FACE 5 - Position	-	Normal
			 0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,		0.0f, 0.0f,	//A - 16
			 0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f,		1.0f, 0.0f,	//G - 17
			-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f,		1.0f, 1.0f,	//E - 18
			-0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,		0.0f, 1.0f,	//B - 19
			
			// FACE 6 - Position	-	Normal
			-0.5f, -0.5f,  0.5f,	0.0f, -1.0f, 0.0f,		1.0f, 0.0f,	//C - 20
			-0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,		1.0f, 1.0f,	//F - 21
			 0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,		0.0f, 1.0f,	//H - 22	
			 0.5f, -0.5f,  0.5f,	0.0f, -1.0f, 0.0f, 		0.0f, 0.0f	//D - 23
		};
		GLuint indices[36] = {
			0, 1, 2,		2, 3, 0,	// FACE 1 (ABCD)
			4, 5, 6,		6, 7, 4,	// FACE 2 (BEFC)
			8, 9, 10,		10, 11, 8,	// FACE 3 (EGHF)
			12, 13, 14,		14, 15, 12,	// FACE 4 (ADHG)
			16, 17, 18,		18, 19, 16,	// FACE 5 (AGEB)
			20, 21, 22,		22, 23, 20		// FACE 6 (CFHD)
		};

		
		//jaw = Jaw();

		

		va = new VertexArray();
		va->Bind();
//		vb = new VertexBuffer(vertPos, 192 * sizeof(GLfloat));
//		vb = new VertexBuffer(jaw.GetData(), jaw.GetCount() * sizeof(GLfloat) / 2);
		vb = new VertexBuffer(jaw);
		//		vb->Bind();
		//		vb->SetData(vertPos, 28 * sizeof(GLfloat));


		VertexArrayAttribute* vaa = new VertexArrayAttribute{
			0, 3, GL_FLOAT, GL_FALSE, "Position"
		};

		VertexArrayAttribute* vaa1 = new VertexArrayAttribute{
			1, 3, GL_FLOAT, GL_FALSE, "Normal"
		};

		VertexArrayAttribute* vaa2 = new VertexArrayAttribute{
			2, 2, GL_FLOAT, GL_FALSE, "TexCoords"
		};

		VertexArrayAttribute* vaa3 = new VertexArrayAttribute{
			3, 1, GL_FLOAT, GL_FALSE, "TexID"
		};
		
		VertexBufferLayout* vbl = new VertexBufferLayout();
		vbl->Add(vaa);
		vbl->Add(vaa1);
		vbl->Add(vaa2);
		vbl->Add(vaa3);
		
		va->AddLayout(vbl, vb);

		//		ib = new IndexBuffer(indices, 15);
		ib = new IndexBuffer();
		ib->Bind();
	//	ib->SetData(indices, 36);
		ib->SetData(jaw.GetIndices(), jaw.GetIndexCount());

		std::string fileName = "res/Shaders/cube_shader.shader";
		shader = new Shader(fileName);
		shader->Bind();

		GLuint diffuseSample = Texture::LoadTexture("res/textures/crate_texture_diffuse.png");
		GLuint specularSample = Texture::LoadTexture("res/textures/crate_texture_specular.png");
		GLuint emissionSample = Texture::LoadTexture("res/textures/matrix.jpg");
		Texture::Bind(diffuseSample, 0);
		Texture::Bind(specularSample, 1);
		Texture::Bind(emissionSample, 2);

		
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
		Test::OnUpdate(deltaTime);
	}
	void Cube::OnRender(Renderer& renderer, float deltaTime)
	{
		Test::OnRender(renderer, deltaTime);
	//	float angle = (float)glfwGetTime() / 5.0f;

		static float timer = glfwGetTime();
		float angle = (glfwGetTime() - timer) * 20;
		timer = glfwGetTime();

		glm::mat4 rotate(
			glm::cos(angle), glm::sin(angle), 0.0f, 0.0f,
			-sin(angle), glm::cos(angle), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		float ambient[3] = {1.0f, 0.5f, 0.31f};
		float diffuse[3] = {1.0f, 0.5f, 0.31f};
		float specular[3] = { 0.5f, 0.5f, 0.5f};
		float shininess = 32.0f;

		float lightAmbient[3] = {	0.2f, 0.2f, 0.2f };
		float lightDiffuse[3] = {	0.5f, 0.5f, 0.5f };
		float lightSpecular[3] = {	1.0f, 1.0f, 1.0f };





		//	const float radius = 5.0f;
		camera->SetX(glm::sin(glm::radians(m_angle)) * 10.0f);
		camera->SetZ(glm::cos(glm::radians(m_angle)) * 10.0f);
		camera->SetLookAt(m_LookAt);

		glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f),
			glm::vec3(translate[0], translate[1], translate[2]));// *glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
		model_matrix = glm::rotate(model_matrix, angle * 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		view_matrix = camera->GetMatrix();// , angle * 2.5f, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 mvp = proj_matrix * view_matrix * model_matrix;
		glm::mat4 model = model_matrix;
		glm::mat3 transInv = glm::mat3(glm::transpose(glm::inverse(model)));

		shader->SetUniform1f("u_Time", angle);

		shader->SetUniformMat4f("u_MVP", mvp);
		shader->SetUniformMat4f("u_MODEL", model);
		shader->SetUniformMat3f("u_TransInv", transInv);
//		shader->SetUniform3fv("u_LightPos", lightPosition);

		shader->SetUniform3fv("light.direction", &(camera->GetFront()[0]));

		shader->SetUniform3fv("light.position", lightPosition);
		shader->SetUniform3fv("light.ambient", lightAmbient);
		shader->SetUniform3fv("light.diffuse", lightDiffuse);
		shader->SetUniform3fv("light.specular", lightSpecular);

		shader->SetUniform1f("light.cutOff", glm::cos(12.5f));
		shader->SetUniform1f("light.outerCutOff", glm::cos(17.5f));


	//	shader->SetUniform3fv("material.ambient", ambient);
		shader->SetUniform1i("material.diffuse", 0);
		shader->SetUniform1i("material.specular", 1);
		shader->SetUniform1i("material.emission", 2);
//		shader->SetUniform3fv("material.diffuse", diffuse);
//		shader->SetUniform3fv("material.specular", specular);
		shader->SetUniform1f("material.shininess", shininess);

		shader->SetUniform1f("light.constant", 1.0f);
		shader->SetUniform1f("light.linear", 0.09f);
		shader->SetUniform1f("light.quadratic", 0.032f);


	//	float cameraPos[3] = { camera->GetX(), camera->GetY(), camera->GetZ() };
		shader->SetUniform3fv("u_CameraPos", &(camera->GetPosition()[0]));
		
		renderer.Draw(va, ib, shader);
		jaw.OnUpdate(angle / 10.0f);
	}
	void Cube::OnImGuiRender()
	{
		ImGui::SliderFloat3("Position", translate, -15.0f, 15.0f);
		ImGui::SliderFloat("Camera Position", &m_angle, -180, 180);
		ImGui::SliderFloat3("Camera Look At", &(m_LookAt.x), -10, 10);
	}
}