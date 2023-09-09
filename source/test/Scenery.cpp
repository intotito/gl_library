#include <test/Scenery.hpp>
#include<VertexBufferLayout.hpp>
#include<texture/Texture.hpp>
#include <vendor/glm/glm.hpp>
#include<Cubex.hpp>
#include<Jaw.hpp>
#include<Sphere.hpp>
#include<Plane.hpp>

namespace Test {

	Scenery::Scenery(std::string testName) : Test(testName), scene(nullptr){
		Sphere* sphere = new Sphere(12, 24);
		sphere->SetPosition(glm::vec3(-2.0f, 5.0f, 1.0f));
		
		scene = new Scene();
		Cubex* cube = new Cubex();
		Cubex* cube1 = new Cubex();
		cube1->SetPosition(vec3(0.0f, 2.5f, -6.0f));
	//	cube1->SetRotation(vec3(0.0f, glm::radians(45.0f), 0.0f));
		cube1->SetScale(vec3(10.0f, 5.0f, 0.1f));

		cube->SetScale(vec3(10.0f, 0.1f, 12.0f));
//		cube->SetRotation(vec3(0.0f, glm::radians(45.0f), 0.0f));
		cube->SetPosition(vec3(0.0f, 0.0f, 0.0f));
		Plane* plane = new Plane();
	//	Jaw* jaw = new Jaw();
		vec3 pos = sphere->GetPosition();
		scene->Add(sphere);
		scene->Add(cube);
		scene->Add(cube1);
		scene->GetCamera()->SetLookAt(pos);
	//	scene->Add(jaw);
//		scene->AddTexture(unsigned int)
	}

	Scenery::~Scenery() {
		delete scene;
	}
	void Scenery::OnUpdate(float deltaTime)
	{
		scene->OnUpdate(deltaTime);
	}
	void Scenery::OnRender(Renderer& renderer)
	{
		static float timer = glfwGetTime();
		float deltaTime = glfwGetTime() - timer;
		timer = glfwGetTime();
		scene->LoadUniforms(timer);
		OnUpdate(deltaTime * 10.0f);
		renderer.Draw(scene->GetVertexArray(), scene->GetIndexBuffer(), scene->GetShader());
//		std::cout << "Delta time: " << deltaTime << std::endl;
	}
	void Scenery::OnImGuiRender()
	{
	}

	void Scenery::OnStart()
	{
		scene->OnStart();
		std::cout << "Scenery OnStart Called()" << std::endl;
	}
}