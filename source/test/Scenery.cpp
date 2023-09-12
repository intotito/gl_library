#include <test/Scenery.hpp>
#include<VertexBufferLayout.hpp>
#include<texture/Texture.hpp>
#include <vendor/glm/glm.hpp>
#include<Cubex.hpp>
#include<Jaw.hpp>
#include<Sphere.hpp>
#include<Plane.hpp>
#include<Cylinder.hpp>
#include<HollowCube.hpp>

namespace Test {

	Scenery::Scenery(std::string testName) : Test(testName), scene(nullptr){
		HollowCube* hc = new HollowCube();

		Sphere* sphere = new Sphere(8, 16);
		sphere->SetPosition(vec3(0.0f, 6.0f, 1.5f));
		Cylinder* cyl = new Cylinder(12);
		cyl->SetScale(vec3(0.25f, 5.0f, 0.25f));
		cyl->SetPosition(vec3(0.0f, 2.51f, 0.0f));
	//	cyl->SetRotation(vec3(glm::radians(60.0f), 0.0f, 0.0f));
		Plane* plane = new Plane();
		plane->SetScale(vec3(10.0f, 10.0f, 1.0f));
		plane->SetRotation(vec3(-glm::radians(90.0f), 0.0f, 0.0f));
		scene = new Scene();
		
		scene->Add(cyl);
		scene->Add(plane);
		scene->Add(sphere);

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