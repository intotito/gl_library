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
#include<HollowCylinder.hpp>

namespace Test {

	Scenery::Scenery(std::string testName) : Test(testName), scene(nullptr){
		HollowCylinder* hc = new HollowCylinder(24, 0.375f);
		HollowCube* hcube = new HollowCube();
		hc->SetScale(vec3(5.0f, 5.0f, 2.0f));
		hcube->SetScale(vec3(5.0f, 5.0f, 1.0f));
		hcube->SetPosition(vec3(0.0f, -3.0f, 1.0f));
//		hcube->SetPosition(vec3(0.0f, 0.0f, 5.0f));
		Sphere* sphere = new Sphere(12, 24);
	//	sphere->SetPosition(vec3(0.0f, 0.0f, -3.0f));
		sphere->SetScale(vec3(5.0f * 0.75f));
		Jaw* cyl = new Jaw();
//		cyl->SetScale(vec3(0.25f, 5.0f, 0.25f));
		cyl->SetPosition(vec3(0.0f, 5.0f, 0.0f));
	//	cyl->SetRotation(vec3(glm::radians(90.0f), 0.0f, 0.0f));
		cyl->SetScale(vec3(5.0f, 5.0f, 5.0f));
		Plane* plane = new Plane();
	//	plane->SetRotation(vec3(-glm::radians(90.0f), 0.0f, 0.0f));
		scene = new Scene();
//		Plane* plane = new Plane();
	//	plane->SetScale(vec3(10.0f));

		scene->Add(hcube);
		scene->Add(cyl);	
		scene->Add(sphere);
	
		Cubex* cube = new Cubex();
		cube->SetScale(vec3(5.0f));
		scene->Add(hc);

	}

	Scenery::~Scenery() {
		delete scene;
	}
	void Scenery::OnUpdate(float deltaTime)
	{
		Test::OnUpdate(deltaTime);
		scene->OnUpdate(deltaTime);
	}
	void Scenery::OnRender(Renderer& renderer, float deltaTime)
	{
		scene->LoadDeltaTimeUniform(deltaTime);
		OnUpdate(deltaTime);
		renderer.Draw(scene->GetVertexArray(), scene->GetIndexBuffer(), scene->GetShader());
//		std::cout << "Delta time: " << deltaTime << std::endl;
	}
	void Scenery::OnImGuiRender()
	{
	}

	void Scenery::OnStart()
	{
		std::vector<std::string> ve;
		ve.push_back("res/textures/Camo.png");
		ve.push_back("res/textures/Camouflage.jpg");
		ve.push_back("res/textures/matrix.jpg");
		scene->LoadTextures(ve);
		scene->OnStart();
		std::cout << "Scenery OnStart Called()" << std::endl;
	}

	void Scenery::OnKeyPressed(event::Event* event)
	{
		int keycode = event->GetKeyCode();
		std::cout << "Okidokiokokokooikokojfisjdifojoasld;j" << std::endl;
		if (keycode == GLFW_KEY_UP)
		{
			scene->GetCamera()->MoveForward();
		} else if (keycode == GLFW_KEY_DOWN)
		{
			scene->GetCamera()->MoveBackward();
		}
		else if (keycode == GLFW_KEY_LEFT)
		{
			scene->GetCamera()->StrafLeft();
		}
		else if (keycode == GLFW_KEY_RIGHT)
		{
			scene->GetCamera()->StrafRight();
		}
	}

}