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
		hc->SetScale(vec3(5.0f, 5.0f, 1.0f));
		Sphere* sphere = new Sphere(12, 24);
	//	sphere->SetPosition(vec3(0.0f, 0.0f, -3.0f));
		sphere->SetScale(vec3(5.0f * 0.75f));
		Cylinder* cyl = new Cylinder(24);
//		cyl->SetScale(vec3(0.25f, 5.0f, 0.25f));
		cyl->SetPosition(vec3(0.0f, 0.0f, 3.0f));
		cyl->SetRotation(vec3(glm::radians(90.0f), 0.0f, 0.0f));
	//	Plane* plane = new Plane();
		cyl->SetScale(vec3(5.0f * 0.75f, 3.0f, 5.0f * 0.75f));
	//	plane->SetRotation(vec3(-glm::radians(90.0f), 0.0f, 0.0f));
		scene = new Scene();
		
	//	scene->Add(cyl);
	//	scene->Add(plane);
		scene->Add(hc);
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